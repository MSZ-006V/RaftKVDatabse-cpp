# pragma once

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>

template<typename K, typename V>
class node{
public:
    node() {}
    node(K key, V val, int level);
    ~node();

    K getKey() const;
    V getVal() const;
    void setValue(V val);

    node<K, V> **forward;
    int node_level;

private:
    K key;
    V value
};

// & 是Boost库对序列化操作符的重载，用于同时支持序列化和反序列化
// 类似于标准I/O操作符<<和>>，根据传入的archive的类型（输入流或是输出流）
// 自动决定执行序列化还是反序列化功能
// & 是序列化流程的核心操作符，通过自动判断archive类型实现双向数据流
template<typename K, typename V>
class SkipListDump{
public:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &archive, const unsigned int version){
        archive &keyDumpVT_;
        archive &valDumpVT_;
    }
    std::vector<K> keyDumpVT_;
    std::vector<V> valDumpVT_;

    void insert(const node<K, V> &node);
};

template<typename K, typename V>
class SkipList{
public:
    SkipList(int max_level);
    ~SkipList();

    void displayList();

    int getRandomLevel();
    node<K, V> *createNode(K, V, int);

    int insertElement(K, V);
    bool searchElement(K, V &value);
    void deleteElement(K);
    void insertSetElement(K &, V &);

    std::string dumpFile();
    void loadFile(const std::string &dumpStr);

    void clear(node<K, V> *);
    int size();
private:
    void getKeyValuefromString(const std::string &str, std::string *key, std::string *value);
    bool isValidString(const std::string &str);
private:
    std::mutex m_mtx;

    // Maximum level of the skip list
    int max_level;
    // Current level of skip list
    int skiplist_level;

    node<K, V> *head;

    std::ofstream file_writer;
    std::ifstream file_reader;

    // Skiplist current element count
    int skiplist_element_count;
};