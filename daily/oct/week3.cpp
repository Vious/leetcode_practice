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


/* 2530. Maximal Score After Applying K Operations */
long long maxKelements(std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::less<>> pque;
    for (auto ele : nums) {
        pque.push(ele);
    }
    long long score = 0;
    for (int i = 0; i < k; i++) {
        int topEle = pque.top();
        pque.pop();
        score += (long long) topEle;
        topEle = std::ceil((double)topEle / 3);
        pque.push(topEle);
    }
    return score;
}

/* 2938. Separate Black and White Balls */
long long minimumSteps(std::string s) {
    long long result = 0;
    size_t length = s.size();
    size_t left = 0, right = s.size() - 1;
    while(left < right) {
        while(left < length && s[left] == '0') {
            left++;
        }
        while(right > 0 && s[right] == '1') {
            right--;
        }
        if (left < right) {
            std::swap(s[left], s[right]);
            result += (right - left);
        }
    }
    return result;
}


/* 1405. Longest Happy String */
std::string longestDiverseString(int a, int b, int c) {
    // std::pair<char, int> myPairs;
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::less<>> pque;
    if (a > 0) {
        pque.push(std::make_pair(a, 'a'));
    }
    if (b > 0) {
        pque.push(std::make_pair(b, 'b'));
    }
    if (c > 0) {
        pque.push(std::make_pair(c, 'c'));
    }
    std::string result = "";
    size_t indx = 0;
    while(!pque.empty()) {
        auto topEle = pque.top();
        pque.pop();
        if (indx >= 2 and result[indx - 1] == topEle.second and result[indx-2] == topEle.second) {
            if (pque.empty()) {
                break;
            }
            auto tmpEle = pque.top();
            pque.pop();
            result += tmpEle.second;
            tmpEle.first--;
            indx++;
            if(tmpEle.first > 0) {
                pque.push(tmpEle);
            }
        } else {
            result += topEle.second;
            topEle.first--;
            indx++;
        }
        if(topEle.first > 0) {
            pque.push(topEle);
        }
    }
    return result;
}


int main()
{
    std::cout << "2530. Maximal Score After Applying K Operations: " << std::endl;
    std::vector<int> nums = {10, 10, 10, 10, 10};
    std::cout << maxKelements(nums, 5) << std::endl;

    std::vector<int> nums2 = {1, 10, 3, 3, 3};
    std::cout << maxKelements(nums2, 3) << std::endl;


    std::cout << "2938. Separate Black and White Balls: " << std::endl;
    std::cout << minimumSteps("101") << std::endl;
    std::cout << minimumSteps("100") << std::endl;
    std::cout << minimumSteps("0111") << std::endl;

    std::cout << "1405. Longest Happy String: " << std::endl;
    std::cout << longestDiverseString(1, 1, 7) << std::endl;

    return 0;
}