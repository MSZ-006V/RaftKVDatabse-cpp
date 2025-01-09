# pragma once

#include<fstream>
#include<mutex>

class Persister{
private:
    void clearRaftState();
    void clearSnapShot();
    void clearStateNSnapShot();

    std::mutex m_mtx;
    std::mutex m_raftState;
    std::mutex m_snapShot;

    // raftState和snapShot的文件名
    const std::string m_raftStateFilename;
    const std::string m_snapShotFilename;
    // raftState和snapShot的输出流
    std::ofstream m_raftStateOutStream;
    std::ofstream m_snapShotOutStream;

    long long m_raftStateSize;
public:
    explicit Persister(int me);
    ~Persister();

    void save(std::string raftState, std::string snapShot);

    std::string readSnapShot();

    void saveRaftState(const std::string& data);
    std::string readRaftState();

    long long getRaftStateSize();

};
