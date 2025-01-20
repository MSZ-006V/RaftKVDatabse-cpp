#pragma once
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <google/protobuf/service.h>
#include <algorithm>
#include <algorithm>  // 包含std::generate_n()和std::generate()函数的头文件
#include <functional>
#include <iostream>
#include <map>
#include <random>  // 包含std::uniform_int_distribution类型的头文件
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class RpcChannel: public google::protobuf::RpcChannel{
public:
    void CallMethod(const google::protobuf::MethodDescriptor *method, 
                    google::protobuf::RpcController *controller,
                    const google::protobuf::Message *request, 
                    google::protobuf::Message *response,
                    google::protobuf::Closure *done) override;

    RpcChannel(string ip, short port, bool connectNow);

private:
    int m_client_fd;
    const std::string m_ip;
    const uint16_t m_port;

    bool newConnect(const char *ip, uint16_t port, std::string *err_msg);

}