#include "rpcchannel.h"

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
        
    }


}

bool RpcChannel::newConnect(const char *ip, uint16_t port, std::string *err_msg){
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1){
        char errtxt[512] = {0};
        sprintf(errtxt, "create socket error! errno:%d", errno);
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
        sprintf(errtxt, "connect fail! errno:%d", errno);
        m_client_fd = -1;
        *err_msg = errtxt;
        return false;
    }
    m_client_fd = client_fd;
    return true;
}