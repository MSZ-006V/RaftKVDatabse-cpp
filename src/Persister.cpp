#include"Persister.h"
#include"util.h"

Persister::Persister(int me)
:m_raftStateFilename("raftstatePersist" + std::to_string(me) + ".txt"),
m_snapShotFilename("snapshotPersist" + std::to_string(me) + ".txt"),
m_raftStateSize(0) {
    bool fileOPenFlag = true;
    std::fstream file(m_raftStateFilename, std::ios::out | std::ios::trunc);
    if(file.is_open()){
        file.close();
    }
    else{
        fileOPenFlag = false;
    }

    file = std::fstream(m_snapShotFilename, std::ios::out | std::ios::trunc);
    if(file.is_open()){
        file.close();
    }
    else{
        fileOPenFlag =false;
    }

    if(!fileOPenFlag){
        DebugPrint("[func-Persister::Persister] file open error");
    }
    m_raftStateOutStream.open(m_raftStateFilename);
    m_snapShotOutStream.open(m_snapShotFilename);
}

Persister::~Persister(){
    if(m_raftStateOutStream.is_open()){
        m_raftStateOutStream.close();
    }
    if(m_snapShotOutStream.is_open()){
        m_snapShotOutStream.close();
    }
}

void Persister::clearRaftState(){
    m_raftStateSize = 0;
    if(m_raftStateOutStream.is_open()){
        m_raftStateOutStream.close();
    }
    // reopen the outstream
    m_raftStateOutStream.open(m_raftStateFilename, std::ios::out | std::ios::trunc);
}

void Persister::clearSnapShot(){
    if(m_snapShotOutStream.is_open()){
        m_snapShotOutStream.close();
    }
    // reopen the outstream
    m_snapShotOutStream.open(m_snapShotFilename, std::ios::out | std::ios::trunc);
}

void Persister::clearStateNSnapShot(){
    clearRaftState();
    clearSnapShot();
}

void Persister::save(std::string raftState, std::string snapShot){
    clearStateNSnapShot(); // close and reopen outstream;
    m_raftStateOutStream << raftState;
    m_snapShotOutStream << snapShot;
}

std::string Persister::readSnapShot(){
    std::lock_guard<std::mutex> lock(m_mtx);
    
    std::fstream ifs(m_snapShotFilename, std::ios_base::in);
    if(!ifs.good()){
        return "";
    }
    std::string snapShot;
    ifs >> snapShot;
    ifs.close();

    return snapShot;
}

void Persister::saveRaftState(const std::string& data){
    std::lock_guard<std::mutex> lock(m_mtx);
    clearRaftState();
    m_raftStateOutStream << data;
    m_raftStateSize += data.size();
}

std::string Persister::readRaftState(){
    std::lock_guard<std::mutex> lock(m_mtx);

    std::fstream ifs(m_raftStateFilename, std::ios_base::in);
    if(!ifs.good()){
        return "";
    }
    std::string raftState;
    ifs >> raftState;
    ifs.close();
    return raftState;
}

long long Persister::getRaftStateSize(){
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_raftStateSize;
}