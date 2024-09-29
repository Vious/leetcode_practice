#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <memory>

/* 432. All O`one Data Structure */
// struct TheOne {
//     std::string mKey;
//     int count = 0;
//     TheOne(std::string key) {
//         mKey = key;
//         count = 1;
//     }
// };

struct cmp {
    bool operator() (const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) const {
        return a.second < b.second;
    }
};


class AllOne {
private:
    std::set<std::pair<int, std::string>> myKeySet;
    std::unordered_map<std::string, int> hashMap;
public:
    AllOne() {

    }
    
    void inc(std::string key) {
        int num = hashMap[key];
        hashMap[key]++;
        auto iter = myKeySet.find(std::make_pair(num, key));
        if (iter != myKeySet.end()) {
            myKeySet.erase(iter);
            myKeySet.insert(std::make_pair(hashMap[key], key));
        } else {
            myKeySet.insert(std::make_pair(hashMap[key], key));
        }
    }
    
    void dec(std::string key) {
        if (!myKeySet.empty()) {
            int num = hashMap[key];
            if (num > 1) {
                auto iter = myKeySet.find(std::make_pair(num, key));
                hashMap[key]--;
                myKeySet.erase(iter);
                myKeySet.insert(std::make_pair(hashMap[key], key));
            } else {
                hashMap.erase(key);
                myKeySet.erase(std::make_pair(num, key));
            }
        }
    }
    
    std::string getMaxKey() {
        if (!myKeySet.empty()) {
            return (myKeySet.rbegin())->second;
        } else {
            return "";
        }
    }
    
    std::string getMinKey() {
        if (!myKeySet.empty()) {
            return (myKeySet.begin())->second;
        } else {
            return "";
        }
    }
};

int main()
{   
    std::unique_ptr<AllOne> allOne = std::make_unique<AllOne>();
    allOne->inc("hello");
    allOne->inc("hello");
    std::cout << allOne->getMaxKey() << std::endl; // return "hello"
    std::cout << allOne->getMinKey() << std::endl; // return "hello"
    allOne->inc("leet");
    std::cout << allOne->getMaxKey() << std::endl; // return "hello"
    std::cout << allOne->getMinKey() << std::endl; // return "leet"
    return 0;
}