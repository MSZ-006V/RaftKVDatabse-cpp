# pragma once

#include"skiplist.h"

template<typename K, typename V>
node<K, V>::node(K key, V val, int level){
    this->key = key;
    this->value = val;
    this->node_level = level;
    this->forward = new node<K, V> *[level + 1];

    memset(this->forward, 0, sizeof(node<K, V> *) * (level + 1));
}

template<typename K, typename V>
node<K, V>::~node(){
    delete[] forward;
}

template<typename K, typename V>
K node<K, V>::getKey() const{
    return this->key;
}

template<typename K, typename V>
V node<K, V>::getVal() const{
    return this->value;
}

template<typename K, typename V>
void node<K, V>::setValue(V val){
    this->value = val;
}


template<typename K, typename V>
void SkipListDump<K, V>::insert(const node<K, V> &node){
    keyDumpVT_.emplace_back(node.getKey());
    valDumpVT_.emplace_back(node.getVal());
}


template<typename K, typename V>
SkipList<K, V>::SkipList(int max_level){
    this->max_level = max_level;
    this->skiplist_level = 0;
    this->skiplist_element_count = 0;

    K k;
    V v;
    this->head = new node<K, V>(k, v, max_level);
}

template<typename K, typename V>
SkipList<K, V>::~SkipList(){
    // 首先关闭输入输出文件流，然后再执行析构函数
    if(file_writer.is_open()) file_writer.close();
    if(file_reader.is_open()) file_reader.close();

    // 递归删除跳表
    if(head->forward[0] != nullptr){
        clear(head->forward[0]);
    }
    delete (head);
}

template<typename K, typename V>
void SkipList<K, V>::displayList(){

}


template<typename K, typename V>
int SkipList<K, V>::getRandomLevel(){

}

template<typename K, typename V>
node<K, V> *SkipList<K, V>::createNode(K k, V v, int level){

}

template<typename K, typename V>
int SkipList<K, V>::insertElement(K k, V v){

}

template<typename K, typename V>
bool SkipList<K, V>::searchElement(K k, V &v){

}

template<typename K, typename V>
void SkipList<K, V>::deleteElement(K k){

}

template<typename K, typename V>
void SkipList<K, V>::insertSetElement(K &k, V &v){

}

template<typename K, typename V>
std::string SkipList<K, V>::dumpFile(){

}

template<typename K, typename V>
void SkipList<K, V>::loadFile(const std::string &dumpStr){

}

template<typename K, typename V>
void SkipList<K, V>::clear(node<K, V> *node){

}

template<typename K, typename V>
int SkipList<K, V>::size(){

}