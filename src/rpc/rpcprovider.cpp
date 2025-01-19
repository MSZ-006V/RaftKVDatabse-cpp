#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <string>
#include "rpcprovider.h"
#include "rpcheader.pb.h"
#include "util.h"

void RpcProvider::notifyService(google::protobuf::Service *service){
    ServiceInfo service_info;
    
    // google::protobuf::Service 是基类对象，protobuf生成的所有service类都会继承这个类
    // 因此这里是动态多态，使用基类指针指向派生类对象，调用用户自定义的service方法
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();

    std::string service_name = pserviceDesc->name();
    int methodCnt = pserviceDesc->method_count();

    std::cout << "service_name:" << service_name << std::endl;

    for(int i = 0; i < methodCnt; ++i){
        const google::protobuf::MethodDescriptor *pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.m_methodMap.insert({method_name, pmethodDesc})
    }

    service_info.m_service = service;
    m_serviceMap.insert({service_name, service_info});
}

void RpcProvider::run(int nodeIndex, short port){
    char *ip_address;
    char host_name[128];
    struct hostent *hent;
    gethostname(host_name, sizeof(host_name));
    hent = gethostbyname(host_name);
    for(int i = 0; hent->h_addr_list[i]; ++i){
        ip_address = inet_ntoa(*(struct in_addr *)(hent->h_addr_list[i]));
    }

    std::string ip = std::string(ip_address); // 获取IP地址
    
    std::string node = "node" + std::to_string(nodeIndex);
    std::ofstream outfile;
    outfile.open("test.conf", std::ios::app);  //打开文件并追加写入
    if (!outfile.is_open()) {
        std::cout << "打开文件失败！" << std::endl;
        exit(EXIT_FAILURE);
    }
    outfile << node + "ip=" + ip << std::endl;
    outfile << node + "port=" + std::to_string(port) << std::endl;
    outfile.close();

    
    muduo::net::InetAddress address(ip, port); // 创建服务器
    m_server = std::make_shared<muduo::net::TcpServer>(&m_eventLoop, address, "RpcProvider");

    // 绑定回调函数
    m_server->setConnectionCallback(
        std::bind(&RpcProvider::OnConnection, // 只有一个参数用一个占位符就可以了
        this, 
        std::placeholders::_1)
    );

    m_server->setMessageCallback(
      std::bind(&RpcProvider::OnMessage, // 有三个参数
      this, 
      std::placeholders::_1, 
      std::placeholders::_2, 
      std::placeholders::_3)
    );

    m_server->setThreadNum(4);

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port << std::endl;

    // 启动网络服务
    m_server->start();
    m_eventloop.loop();
}

void RpcProvider::sendRpcResonse(
    const muduo::net::TcpConnectionPtr &connection, 
    google::protobuf::Message *response){
    std::string response_str;
    if(response->SerializeToString(&response_str)){
        connection->send(response_str);
    }
    else{
        std::cout << "serialize response_str error!" << std::endl;
    }
    // 若加入这一句connection.shutdown()，即是模仿https短连接，发送完消息后断开连接
    // 未加入则是长连接，优化点：加入计时器，统计长时间不发送消息的客户端断开连接
}
void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &connection){
    if(!connection->connect()){
        connection->shutdown();
    }
}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &connection, 
muduo::net::Buffer *buffer, 
muduo::Timestamp){
    std::string recv_buf = buffer->retrieveAllAsString();

    // 使用protobuf对数据流进行解析
    google::protobuf::io::ArrayInputStream array_input(recv_buf.data(), recv_buf.size());
    google::protobuf::io::CodedInputStream coded_input(&array_input);
    uint32_t header_size{};

    code_input.ReadVarint32(&header_size);

    // 已知head的大小，从coded_input中按照长度读取并对变量赋值即可
    RPC::RpcHeader rpcHeader;
    std::string rpc_header_str;
    std::string service_name;
    std::string method_name;

    google::protobuf::io::CodedInputStream::Limit msg_limit = coded_input.PushLimit(header_size);

    coded_input.ReadString(&rpc_header_str, header_size); // 按照head长度，读出整个头部，保存在变量rpc_header_str中
    coded_input.PopLimit(msg_limit); // 恢复之前的限制，以便安全地继续读取其他数据

    uint32_t args_size{};
    if (rpcHeader.ParseFromString(rpc_header_str)) { // 解析rpc_header_str序列化数据，保存到提前定义好的RpcHeader结构中
        service_name = rpcHeader.service_name(); // 读取service name
        method_name = rpcHeader.method_name(); // 读取调用方法名字
        args_size = rpcHeader.args_size(); // 读取参数大小
    } else {
        std::cout << "rpc_header_str:" << rpc_header_str << " parse error!" << std::endl;
        return;
    }

    std::string args_str; // 设置参数的字符流数据
    
    bool read_args_success = coded_input.ReadString(&args_str, args_size); // 直接读取args_size长度的字符串数据
    if (!read_args_success) {
        return;
    }

    auto it_service = m_serviceMap.find(service_name); // 获取service对象
    if(it_service == m_serviceMap.end()){
        // 在可提供服务表service_map中未查找到该服务，报错并返回
        std::cout << "服务：" << service_name << " is not exist!" << std::endl; 
        return;
    }

    auto it_method = it->second.m_methodMap.find(method_name); // 获取method对象
    if(it_method == it->second.m_methodMap.end()){
        // 在可提供方法m_methodMap中未查找到该方法，报错并返回
        std::cout << service_name << ": " << method_name << " is not exist!" << std::endl; 
        return;
    }

    // 获取service和method对象
    google::protobuf::Service *service = it_service->second.m_service;
    const google::protobuf::MethodDescriptor *method = it_method->second;

    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(args_str)) {
        std::cout << "request parse error, content:" << args_str << std::endl;
        return;
    }
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 绑定回调函数，这个回调会在RPC方法执行完成后调用
    google::protobuf::Closure *done = 
    google::protobuf::NewCallback<RpcProvider, const muduo::net::TcpConnectionPtr &, google::protobuf::Message *>(
        this, 
        &RpcProvider::SendRpcResponse, 
        connection, 
        response);

    // 调用method完成任务，完成后调用回调函数done发送消息
    service->CallMethod(method, nullptr, request, response, done);
}

RpcProvider::~RpcProvider(){
    std::cout << "[func - RpcProvider::~RpcProvider()]: ip和port信息：" << m_server->ipPort() << std::endl;
    m_eventLoop.quit();
}