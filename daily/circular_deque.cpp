#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>
#include <cmath>
#include <sstream>


/* 641. Design Circular Deque */
class MyCircularDeque {
private:
    int capacity;
    int size;
    int overrunCnt = 0;
    typename std::vector<int>::size_type front = 0;
    typename std::vector<int>::size_type rear = 0;

    std::vector<int> mqBuffer;

public:
    MyCircularDeque(int k) {
        capacity = (k > 0) ? k : 0;
        front = 0;
        rear = k - 1;
        size = 0;
        mqBuffer.reserve(capacity);
    }
    
    bool insertFront(int value) {
        if (!isFull()) {
            if (capacity > 0) {
                front = (front - 1 + capacity) % capacity;
                mqBuffer[front] = value;
                size++;
                return true;
            }
        }
        return false;
    }
    
    bool insertLast(int value) {
        if (!isFull()) {
            if (capacity > 0) {
                rear = (rear + 1) % capacity;
                mqBuffer[rear] = value;
                size++;
                return true;
            }
        }
        return false;
    }
    
    bool deleteFront() {
        if (!isEmpty()) {
            front = (front + 1) % capacity;
            size--;
            return true;
        }
        return false;
    }
    
    bool deleteLast() {
        if (!isEmpty()) {
            rear = (rear - 1 + capacity) % capacity;
            size--;
            return true;
        }
        return false;
    }
    
    int getFront() {
        return isEmpty() ? -1 : mqBuffer[front];
    }
    
    int getRear() {
        if (!isEmpty()) {
            return mqBuffer[rear];
        }
        return -1;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};
