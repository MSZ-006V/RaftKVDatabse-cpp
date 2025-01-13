#pragma once
#include <google/protobuf/descriptor.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <functional>
#include <string>
#include <unordered_map>
#include "google/protobuf/service.h"

class RpcProvider{
private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventloop;
    std::share_ptr<muduo::net::TcpServer> m_server;

    // service服务类型信息
    struct ServiceInfo{
        google::protobuf::Service *m_service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> m_methodMap;
    };

    // 存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    void onConnection(const muduo::net::TcpConnectionPtr &);
    void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp);
    void sendRpcResonse(const muduo::net::TcpConnectionPtr &, google::protobuf::Message *);
public:
    // 框架提供给外部使用的方法，可以发布rpc方法的函数接口
    void notifyService(google::protobuf::Service *service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void run(int nodeIndex, short port);
    
    ~RpcProvider();
}