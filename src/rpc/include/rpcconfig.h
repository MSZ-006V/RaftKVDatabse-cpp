#pragma once
#include <string>
#include <unordered_map>

class RpcConfig{
public:
    void loadConfigFile(const char *config_file);
    std::string load(const std::string &key);
private:
    std::unordered_map<std::string, std::string> m_configmap;
    void trim(std::string &src_buf);
}