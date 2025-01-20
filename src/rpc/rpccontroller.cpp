#include "rpccontroller.h"

RpcController::RpcController(): m_failed(false), m_error_info("") {}

void RpcController::reset(){
    m_failed = false;
    m_error_info = "";
}

void RpcController::failed() { return m_failed; }

std::string RpcController::getErrorText() const { return m_error_info; }

void RpcController::setFailed(const std::string& reason){
    m_failed = true;
    m_error_info = reason;
}