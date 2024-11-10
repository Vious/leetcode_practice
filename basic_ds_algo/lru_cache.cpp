#include <iostream>
#include <queue>
#include <thread>
#include <unordered_map>

/* 146. LRU Cache */
/*  */
class Node {
public:
    int mKey;
    int mValue;

    Node* next;
    Node* prev;

    Node(int key = 0, int value = 0) : mKey(key), mValue(value) {}
};

class LRUCache {
private:
    int m_capacity;
    Node *dummy;
    std::unordered_map<int, Node*> myHashMap;

    void remove(Node *aNode) {
        aNode->prev->next = aNode->next;
        aNode->next->prev = aNode->prev;
    }

    void push(Node *aNode) {
        aNode->prev = dummy;
        aNode->next = dummy->next;
        aNode->prev->next = aNode;
        aNode->next->prev = aNode;
    }

    Node* getNode(int key) {
        if (myHashMap.find(key) != myHashMap.end()) {
            // Node *theNode = myHashMap[key];
            Node *theNode = myHashMap.find(key)->second;
            remove(theNode);
            push(theNode);
            return theNode;
        } else {
            return nullptr;
        }
    }

public:
    LRUCache(int capacity) {
        // m_capacity = capacity;
        m_capacity = capacity;
        dummy = new Node();
        dummy->next = dummy;
        dummy->prev = dummy;
    }
    
    int get(int key) {
        Node *theNode = getNode(key);
        if (theNode != nullptr) {
            return theNode->mValue;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        Node *theNode = getNode(key);
        if (theNode != nullptr) {
            theNode->mValue = value;
            return;
        } else {
            theNode = new Node(key, value);
            push(theNode);
            myHashMap[key] = theNode;
            if (myHashMap.size() > m_capacity) {
                Node *back = dummy->prev;
                myHashMap.erase(back->mKey);
                remove(back);
                delete back;
                return;
            }
        }
    }
};

// void runTest() {

//     std::cout << "Test Done." << std::endl;
// }

// int main()
// {
//     std::thread task1{runTest};
//     task1.join();

//     return 0;
// }