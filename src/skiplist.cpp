#include"skiplist.h"
#include"config.h"

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
    if(DEBUG){ // only display under DEBUG mode, define in config.h
        std::cout << "\nSkipList display\n";
        for(int i = 0; i < skiplist_level; ++i){
            node<K, V> *node = this->head->forward[i];
            std::cout << "Level " << i << ": ";
            while(node != nullptr){
                std::cout << node->getKey() << ":" << node->getVal() << ";";
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
    }
}


template<typename K, typename V>
int SkipList<K, V>::getRandomLevel(){
    int k = 1;
    while(rand() % 2){
        k++;
    }
    k = (k < max_level)? k : max_level;
    return k;
}

template<typename K, typename V>
node<K, V> *SkipList<K, V>::createNode(K k, V v, int level){
    node<K, V> *n = new node<K, V>(k, v, level);
    return n;
}

template<typename K, typename V>
int SkipList<K, V>::insertElement(K key, V val){
    std::lock_guard<std::mutex> lock(m_mtx);
    node<K, V> *cur = this->head;

    node<K, V> *update[max_level + 1];
    memset(update, 0, sizeof(node<K, V> *) * (max_level + 1));

    for(int i = skiplist_level; i >= 0; --i){
        while(cur->forward[i] != nullptr && cur->forward[i]->getKey() < key){
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    cur = cur->forward[0];
    if(cur != nullptr && cur->getKey() == key){
        std::cout << "key: " << key << ", exists" << std::endl;
        return 1;
    }

    if(cur == nullptr || cur->getKey() != key){
        int randomLevel = getRandomLevel();
        if(randomLevel > skiplist_level){
            for(int i = skiplist_level + 1; i < randomLevel + 1; ++i){
                update[i] = head;
            }
            skiplist_level = randomLevel;
        }

        node<K, V>* insertedNode = createNode(key, val, randomLevel);
        for(int i = 0; i < randomLevel; ++i){
            insertedNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = insertedNode;
        }
        std::cout << "Insert Successfully" << std::endl;
        skiplist_element_count++;
    }

    return 0;
}

// ! 似乎val是多余的变量，搜索不需要val
template<typename K, typename V>
bool SkipList<K, V>::searchElement(K key, V &val){
    std::cout << "-----------------Element searching now-----------------" << std::endl;
    node<K, V> *cur = head;

    // start from the highest level of skiplist
    for(int i = skiplist_level; i >= 0; --i){
        while(cur->forward[i] && cur->forward[i]->getKey() < key){
            cur = cur->forward[i];
        }
    }

    cur = cur->forward[0];
    if(cur && cur->getKey() == key){
        val = cur->getval();
        std::cout << "Found key: " << key << ", value: " << val << std::endl;
        return true;
    }

    std::cout << " Not Found key: " << key << std::endl;
    return false;
}

template<typename K, typename V>
void SkipList<K, V>::deleteElement(K k){
    std::lock_guard<std::mutex> lock(m_mtx);

    return;
}

template<typename K, typename V>
void SkipList<K, V>::insertSetElement(K &key, V &val){
    V nullval;
    if(searchElement(key, nullval)){
        deleteElement(key);
    }
    insertElement(key, val);
}

template<typename K, typename V>
std::string SkipList<K, V>::dumpFile(){
    if(DEBUG){
        std::cout << "-----------------dump file-----------------" << std::endl;
    }
    node<K, V> *node = this->head->forward[0];
    SkipListDump<K, V> dumper;
    while(node != nullptr){
        dumper.insert(*node);
        node = node->forward[0];
    }
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << dumper;
    return ss.str();
}

template<typename K, typename V>
void SkipList<K, V>::loadFile(const std::string &dumpStr){
    if(DEBUG){
        std::cout << "-----------------load file-----------------" << std::endl;
    }
    if(dumpStr.empty()){
        return;
    }
    SkipListDump<K, V> loader;
    std::stringstream iss(loader);
    boost::archive::text_iarchive ia(iss);
    ia >> loader;
    for(int i = 0; i < loader.keyDumpVT_.size(); ++i){
        insertElement(loader.keyDumpVT_[i], loader.valDumpVT_[i]);
    }
}

template<typename K, typename V>
void SkipList<K, V>::clear(node<K, V> *node){
    if(node->forward[0] != nullptr){
        clear(node->forward[0]);
    }
    delete (node);
}

template<typename K, typename V>
int SkipList<K, V>::size(){
    return skiplist_element_count;
}

template<typename K, typename V>
void SkipList<K, V>::getKeyValuefromString(const std::string &str, std::string *key, std::string *value){
    if(isValidString(str)){
        return;
    }
    *key = str.substr(0, str.find(delimiter));
    *value = str.substr(str.find(delimiter) + 1, str.length());
}

template<typename K, typename V>
bool SkipList<K, V>::isValidString(const std::string &str){
    if(str.empty()) return false;
    if(str.find(delimiter) == std::string::npos) return false;
    return true;
}