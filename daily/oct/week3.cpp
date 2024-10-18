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

/* 670. Maximum Swap */
int vecSum(std::vector<int> &nums) {
    size_t size = nums.size();
    int sum = 0;
    for (int i = 0 ; i < size; i++) {
        sum = sum * 10 + nums[i];
    }
    return sum;
}

int maximumSwap(int num) {
    std::vector<int> digits;
    int originalVal = num;
    while(num > 0) {
        digits.emplace_back(num % 10);
        num /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    size_t size = digits.size();
    int maxVal = digits[0];
    bool canSwap = false;
    size_t indx = 0;
    for (int i = 0; i < size - 1; i++) {
        canSwap = false;
        maxVal = digits[i];
        indx = i;
        for (int j = i + 1; j < size; j++) {
            if (digits[j] > digits[i]) {
                canSwap = true;
                indx = digits[j] >= maxVal ? j : indx;
                maxVal = digits[j] >= maxVal ? digits[j] : maxVal;
            }
        }
        if (canSwap) {
            std::swap(digits[i], digits[indx]);
            originalVal = std::max(originalVal, vecSum(digits));
            std::swap(digits[i], digits[indx]);
        }
    }
    return originalVal;
}

/* 2044. Count Number of Maximum Bitwise-OR Subsets */
int backtraceSubOr(std::vector<int> &nums, int &maxVal, int tmp, int level) {
    if (level == nums.size()) {
        return tmp == maxVal? 1 : 0;
    }
    int count1 = backtraceSubOr(nums, maxVal, tmp | nums[level], level + 1);

    int count2 = backtraceSubOr(nums, maxVal, tmp, level + 1);

    return count1 + count2;
}

int countMaxOrSubsets(std::vector<int>& nums) {
    size_t size = nums.size();
    int maxVal = 0;
    for (int i = 0; i < size; i++) {
        maxVal = maxVal | nums[i];
    }
    int tmpVal = 0;
    return backtraceSubOr(nums, maxVal, tmpVal, 0);
}

int main()
{
    std::cout << "2530. Maximal Score After Applying K Operations: " << std::endl;
    // std::vector<int> nums = {10, 10, 10, 10, 10};
    // std::cout << maxKelements(nums, 5) << std::endl;

    // std::vector<int> nums2 = {1, 10, 3, 3, 3};
    // std::cout << maxKelements(nums2, 3) << std::endl;


    std::cout << "2938. Separate Black and White Balls: " << std::endl;
    std::cout << minimumSteps("101") << std::endl;
    std::cout << minimumSteps("100") << std::endl;
    std::cout << minimumSteps("0111") << std::endl;

    std::cout << "1405. Longest Happy String: " << std::endl;
    std::cout << longestDiverseString(1, 1, 7) << std::endl;

    std::cout << "670. Maximum Swap: " << std::endl;
    std::cout << maximumSwap(2736) << std::endl;
    std::cout << maximumSwap(9973) << std::endl;
    std::cout << maximumSwap(1993) << std::endl;

    std::cout << "2044. Count Number of Maximum Bitwise-OR Subsets: " << std::endl;
    std::vector<int> nums1 = {3, 1};
    std::cout << countMaxOrSubsets(nums1) << std::endl;
    std::vector<int> nums2 = {2, 2, 2};
    std::cout << countMaxOrSubsets(nums2) << std::endl;
    std::vector<int> nums3 = {3,2,1,5};
    std::cout << countMaxOrSubsets(nums3) << std::endl;

    return 0;
}