#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>
#include <cmath>
#include <sstream>


/* 1593. Split a String Into the Max Number of Unique Substrings */
void solveSplit(std::string &str, std::unordered_map<std::string, int> &strCntMap, int indx, int &count, int tmpCount) {
    // some pruning
    if (str.size() - indx + tmpCount <= count) {
        return;
    }
    if (indx == str.size()) {
        count = std::max(count, tmpCount);
        return;
    }
    for (int i = indx; i < str.size(); i++) {
        if (strCntMap.find(str.substr(indx, i - indx + 1)) != strCntMap.end()) {
            continue;
        } else {
            strCntMap[str.substr(indx, i - indx + 1)]++;
            tmpCount++;
            solveSplit(str, strCntMap, i + 1, count, tmpCount);
            auto iter = strCntMap.find(str.substr(indx, i - indx + 1));
            strCntMap.erase(iter);
            tmpCount--;
        }
    }
}

int maxUniqueSplit(std::string s) {
    size_t size = s.size();
    if (size <= 1) {
        return size;
    }
    std::unordered_map<std::string, int> strCntMap;
    int count = 0;
    solveSplit(s, strCntMap, 0, count, 0);
    return count;
}


int main()
{
    std::cout << "1593. Split a String Into the Max Number of Unique Substrings: " << std::endl;
    std::cout << "s = \"ababccc\": " << maxUniqueSplit("ababccc") << std::endl;
    std::cout << "s = \"aba\": " << maxUniqueSplit("aba") << std::endl;
    std::cout << "s = \"aa\": " << maxUniqueSplit("aa") << std::endl;

    return 0;
}