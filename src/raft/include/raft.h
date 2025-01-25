#pragma once

constexpr int DISCONNECTED = 0;
constexpr int APPNORMAL = 1;

constexpr int KILLED = 0;
constexpr int VOTED = 1;
constexpr int EXPIRE = 2;
constexpr int NORMAL = 3;

#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include "ApplyMsg.h"
#include "Persister.h"
#include "boost/any.hpp"
#include "boost/serialization/serialization.hpp"
#include "config.h"
#include "monsoon.h"
#include "raftRpcUtil.h"
#include "util.h"

// -------------------------------//
// 选举部分：electionTimeOutTicker(查看是否应该进行选举) 
// -> doElection(发起选举，构造RPC request) 
// -> sendRequestVote(发送RPC request，同时负责接收处理别的客户端发送的response) 
// -> RequestVote(接收别的客户端发送请求，检验是否投票)

// -------------------------------//


class Raft : public raftRpcProctoc::raftRpc{
public:

    void AppendEntries1(const raftRpcProctoc::AppendEntriesArgs *args, raftRpcProctoc::AppendEntriesReply *reply);
    void applierTicker();
    bool CondInstallSnapshot(int lastIncludedTerm, int lastIncludedIndex, std::string snapshot);

    void doElection();
    void doHeartBeat();
    // 每隔一段时间检查睡眠时间内有没有重置定时器，没有则说明超时了
    // 如果有则设置合适睡眠时间：睡眠到重置时间+超时时间

    void electionTimeOutTicker();
    std::vector<ApplyMsg> getApplyLogs();
    int getNewCommandIndex();
    void getPrevLogInfo(int server, int *preIndex, int *preTerm);
    void GetState(int *term, bool *isLeader);
    void InstallSnapshot(const raftRpcProctoc::InstallSnapshotRequest *args, raftRpcProctoc::InstallSnapshotResponse *reply);

    void leaderHearBeatTicker();
    void leaderSendSnapShot(int server);
    void leaderUpdateCommitIndex();

    bool matchLog(int logIndex, int logTerm);
    void persist();
    void RequestVote(const raftRpcProctoc::RequestVoteArgs *args, raftRpcProctoc::RequestVoteReply *reply);
    bool UpToDate(int index, int term);
    int getLastLogIndex();
    int getLastLogTerm();
    void getLastLogIndexAndTerm(int *lastLogIndex, int *lastLogTerm);
    int getLogTermFromLogIndex(int logIndex);
    int GetRaftStateSize();
    int getSlicesIndexFromLogIndex(int logIndex);

    bool sendRequestVote(int server, std::shared_ptr<raftRpcProctoc::RequestVoteArgs> args,
                        std::shared_ptr<raftRpcProctoc::RequestVoteReply> reply, std::shared_ptr<int> votedNum);
    bool sendAppendEntries(int server, std::shared_ptr<raftRpcProctoc::AppendEntriesArgs> args,
                            std::shared_ptr<raftRpcProctoc::AppendEntriesReply> reply, std::shared_ptr<int> appendNums);

    void pushMsgToKvServer(ApplyMsg msg);
    void readPersist(std::string data);
    std::string persistData();

    void Start(Op command, int *newLogIndex, int *newLogTerm, bool *isLeader);

    void Snapshot(int index, std::string snapshot);

    public:
    // 重写基类方法, AppendEntries获取日志, InstallSnapshot获取快照，RequesVote请求投票RPC函数
    void AppendEntries(google::protobuf::RpcController *controller, const ::raftRpcProctoc::AppendEntriesArgs *request,
                        ::raftRpcProctoc::AppendEntriesReply *response, ::google::protobuf::Closure *done) override;
    void InstallSnapshot(google::protobuf::RpcController *controller,
                        const ::raftRpcProctoc::InstallSnapshotRequest *request,
                        ::raftRpcProctoc::InstallSnapshotResponse *response, ::google::protobuf::Closure *done) override;
    void RequestVote(google::protobuf::RpcController *controller, const ::raftRpcProctoc::RequestVoteArgs *request,
                    ::raftRpcProctoc::RequestVoteReply *response, ::google::protobuf::Closure *done) override;
    void init(std::vector<std::shared_ptr<RaftRpcUtil>> peers, int me, std::shared_ptr<Persister> persister,
                std::shared_ptr<LockQueue<ApplyMsg>> applyCh);

    class BoostPersistRaftNode {
    public:
        friend class boost::serialization::access;

        template <class Archive>
        void serialize(Archive &ar, const unsigned int version) {
        ar &m_currentTerm;
        ar &m_votedFor;
        ar &m_lastSnapshotIncludeIndex;
        ar &m_lastSnapshotIncludeTerm;
        ar &m_logs;
        }

        int m_currentTerm;
        int m_votedFor;
        int m_lastSnapshotIncludeIndex;
        int m_lastSnapshotIncludeTerm;

        std::vector<std::string> m_logs;
        std::unordered_map<std::string, int> umap;
    };

private:
    enum Status { Follower, Candidate, Leader };
    Status m_status;
    std::mutex m_mtx;
    std::vector<std::shared_ptr<RaftRpcUtil>> m_peers;
    std::shared_ptr<Persister> m_persister;
    int m_me;
    int m_currentTerm;
    int m_votedFor;

    std::vector<raftRpcProctoc::LogEntry> m_logs; // 日志数组，注意查看这个LogEntry类
    std::vector<int> m_nextIndex;  // 这两个状态的下标从1开始
    std::vector<int> m_matchIndex;

    std::shared_ptr<LockQueue<ApplyMsg>> applyChan;  // client从这里取日志，client与raft通信的接口
  
    // 用于选举超时
    std::chrono::_V2::system_clock::time_point m_lastResetElectionTime;
    // 用于心跳超时
    std::chrono::_V2::system_clock::time_point m_lastResetHearBeatTime;

    int m_lastSnapshotIncludeIndex;
    int m_lastSnapshotIncludeTerm;

    std::unique_ptr<monsoon::IOManager> m_ioManager = nullptr; // fiber协程
}