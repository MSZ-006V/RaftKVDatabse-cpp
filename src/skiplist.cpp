# pragma once

#include"skiplist.h"

template<typename K, typename V>
node<K, V>::node(K key, V val, int level){
    this->key = key;
    this->value = val;
    this->nodeLevel = level;
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