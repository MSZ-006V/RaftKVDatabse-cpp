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

void RpcProvider::sendRpcResonse(const muduo::net::TcpConnectionPtr &connection, google::protobuf::Message *response){
    
}

void RpcProvider::run(int nodeIndex, short port){

}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &connection){

}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &connection, muduo::net::Buffer *buffer, muduo::Timestamp){

}