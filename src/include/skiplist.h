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
    int nodeLevel;

private:
    K key;
    V value
};

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
    SkipList(int level);
    ~SkipList();
private:

};