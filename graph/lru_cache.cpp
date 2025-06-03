#include <iostream>
#include <unordered_map>
#include <vector>

class DListNode {
public:

    DListNode(): key(0), value(0), prev(nullptr), next(nullptr) {};
    DListNode(int key_, int value_): key(key_), value(value_), prev(nullptr), next(nullptr) {};

    int key, value;
    DListNode* prev;
    DListNode* next;
};

class LRUCache {
public:

    LRUCache(int capacity_): capacity(capacity_), size(0) {
        head = new DListNode();
        tail = new DListNode();
        head->next = tail;
        tail->prev = head;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            DListNode* node = new DListNode(key, value);
            cache[key] = node;
            refresh(node);
            size++;
            if (size > capacity) {
                DListNode* removedNode = tail->prev;
                remove(removedNode);
                cache.erase(removedNode->key);
                delete removedNode;
                size--;
            }
        } else {
            DListNode* node = cache[key];
            node->value = value;
            refresh(node);
        }
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        DListNode* node = cache[key];
        refresh(node);
        return node->value;
    }

    void refresh(DListNode *node) {
        remove(node);
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void remove(DListNode *node) {
        if (node->next != nullptr) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }

    std::vector<int> keys() {
        std::vector<int> keyList;
        for (DListNode* p = head->next; p != tail; p = p->next) {
            keyList.push_back(p->key);
        }
        return keyList;
    }

private:
    std::unordered_map<int, DListNode*> cache;
    DListNode* head;
    DListNode* tail;
    int size;
    int capacity;
};


int main() {

    LRUCache cache = LRUCache(5);
    cache.put(1, 2);
    cache.put(2, 2);
    cache.put(3, 2);
    cache.put(4, 2);
    cache.put(5, 2);
    for (const auto& key : cache.keys()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    cache.put(6, 2);
    cache.put(7, 2);
    for (const auto& key : cache.keys()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    return 0;
}

