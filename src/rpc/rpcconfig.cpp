#include "rpcconfig.h"

void RpcConfig::loadConfigFile(const char *config_file){
    // format_example: server_ip=127.0.0.1  -> key: server_ip,  val: 127.0.0.1
    // format_example: address=4000         -> key: address,    val: 4000
    FILE *fs = fopen(config_file, "r");
    if(fs == nullptr){
        std::cout << "Path " << config_file << " is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(!feof(fs)){
        char buffer[512] = {0};
        fgets(buffer, 512, fs);

        std::string read_buf(buffer);
        trim(read_buf);

        if(read_buf[0] == '#' || read_buf.empty()) continue;
        int index = read_buf.find('=') == -1;
        if(index) continue;

        int end = read_buf.find('\n', index);
        std::string key = read_buf.substr(0, index);
        std::string val = read_buf.substr(index + 1, end - index - 1);
        trim(key); trim(val);

        m_configmap.insert({key, val});
    }
    fclose(fs); // close the stream
}

std::string RpcConfig::load(const std::string &key){
    if(!m_configmap.contains(key)){
        return "";
    }
    return m_configmap[key];
}

void RpcConfig::trim(std::string &src_buf){
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1) {
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    idx = src_buf.find_last_not_of(' ');
    if (idx != -1) {
        src_buf = src_buf.substr(0, idx + 1);
    }
}