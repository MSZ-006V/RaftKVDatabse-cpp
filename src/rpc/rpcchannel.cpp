#include "rpcchannel.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include "mprpccontroller.h"
#include "rpcheader.pb.h"
#include "util.h"

RpcChannel::RpcChannel(string ip, short port, bool connectNow): m_ip(ip), m_port(port), m_client_fd(-1){
    if(!connectNow) return;

    std::string err_msg;
    auto rt = newConnect(ip.c_str(), port, &err_msg);
    int tryCount = 3;
    while(!rt && tryCount--){
        std::cout << err_msg << std::endl;
        rt = newConnect(ip.c_str(), port, &err_msg);
    }
}

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method, 
google::protobuf::RpcController *controller, 
const google::protobuf::Message *request, 
google::protobuf::Message *response, 
google::protobuf::Closure *done){
    if(m_client_fd == -1){
        std::string errMsg;
        bool rt = newConnect(m_ip.c_str(), m_port, &errMsg);
        if (!rt){
        DebugPrint("[func-MprpcChannel::CallMethod]重连接ip：{%s} port{%d}失败", m_ip.c_str(), m_port);
        controller->setFailed(errMsg);
        return;
        } 
        else{
        DebugPrint("[func-MprpcChannel::CallMethod]连接ip：{%s} port{%d}成功", m_ip.c_str(), m_port);
        }
    }

    // get the service name and method name
    const google::protobuf::ServiceDescriptor* sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();

    // SerializeToString() 用来序列化service，method，args等参数
    uint32_t args_size{};
    std::string args_str;
    if(request->SerializeToString(&args_str)){
        args_size = args_str.size();
    } 
    else{
        controller->setFailed("serialize request error!");
        return;
    }

    RPC::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_args_size(args_size);

    std::string rpc_header_str;
    if (!rpcHeader.SerializeToString(&rpc_header_str)) {
        controller->setFailed("serialize rpc header error!");
        return;
    }

    // 使用protobuf的CodedOutputStream来构建发送的数据流
    std::string send_rpc_str;  // 用来存储最终发送的数据
    {
        // 创建StringOutputStream写入send_rpc_str
        google::protobuf::io::StringOutputStream string_output(&send_rpc_str);
        google::protobuf::io::CodedOutputStream coded_output(&string_output);

        // 写入header的长度（变长编码）
        coded_output.WriteVarint32(static_cast<uint32_t>(rpc_header_str.size()));

        // 写入rpc_header
        coded_output.WriteString(rpc_header_str);
    }

    // 最后，将请求参数附加到send_rpc_str后面
    send_rpc_str += args_str;

    // send_rpc_str structure = rpc_header_str + args_str
    // rpc_header_str包括service_name, method_name, args_size（只有长度）
    // args_str包括method对应的全部参数args
    // send_rpc_str里面会包括以下信息：header_size, header_str, service_name, method_name, args_size, args_str
    // 然后下面把这个send_rpc_str发送出去，必须是str序列化后的数据

    // 发送RPC request
    while(send(m_client_fd, send_rpc_str.c_str(), send_rpc_str.size(), 0) == -1){
        char errtxt[512] = {0};
        DebugPrint("send error! errno:%d", errtxt);
        close(m_client_fd);

        m_client_fd = -1;
        std::string err_msg;
        bool rt = newConnect(m_ip.c_str(), m_port, &err_msg);
        if(!rt){
            controller->setFailed(err_msg);
            return;
        }
    }

    // 接收RPC response
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if((recv_size = recv(m_client_fd, recv_buf, 1024, 0)) == -1){
        close(m_client_fd);
        m_client_fd = -1;
        char errtxt[512] = {0};
        DebugPrint("receive error! errno:%d", errtxt);
        controller->setFailed(errtxt);
        return;
    }

    if (!response->ParseFromArray(recv_buf, recv_size)) {
        char errtxt[1050] = {0};
        DebugPrint("parse error! response_str:%s", recv_buf);
        controller->setFailed(errtxt);
        return;
    }
}

bool RpcChannel::newConnect(const char *ip, uint16_t port, std::string *err_msg){
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1){
        char errtxt[512] = {0};
        DebugPrint(errtxt, "create socket error! errno:%d", errno);
        m_client_fd = -1;
        *err_msg = errtxt;
        return false;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        close(client_fd);
        char errtxt[512] = {0};
        DebugPrint(errtxt, "connect fail! errno:%d", errno);
        m_client_fd = -1;
        *err_msg = errtxt;
        return false;
    }
    m_client_fd = client_fd;
    return true;
}