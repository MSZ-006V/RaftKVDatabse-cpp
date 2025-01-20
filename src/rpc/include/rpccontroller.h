#pragma once
#include <google/protobuf/service.h>
#include <string>

class RpcController: public google::protobuf::RpcController{
public:
    RpcController();

    void reset();
    void failed();
    std::string getErrorText() const;
    void setFailed(const std::string& reason);

private:
    bool m_failed;
    std::string m_error_info;
};