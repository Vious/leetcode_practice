#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>


using namespace std;

/* 209. Minimum Size Subarray Sum */
int minSubArrayLen(int target, vector<int>& nums) {
    int size = nums.size();
    // std::vector<int> prefixSum(size, 0);
    // prefixSum[0] = nums[0];
    // for (int i = 1; i < size; i++) {
    //     prefixSum[i] += prefixSum[i - 1] + nums[i];
    // }
    int minLen = INT32_MAX;
    int left = 0, tmpSum = 0;
    for (int i = 0; i < size; i++) {
        // tmpSum = prefixSum[i] - prefixSum[left] + nums[left];
        tmpSum += nums[i];
        while(tmpSum >= target) {
            minLen = std::min(minLen, i - left + 1);
            tmpSum -= nums[left];
            left++;
        }
    }
    return minLen == INT32_MAX ? 0 : minLen;
}

/* 713. Subarray Product Less Than K */
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) {
        return 0;
    }
    int size = nums.size();
    int result = 0, left = 0;
    long long tmpMultiply = 1;
    for (int i = 0; i < size; i++) {
        tmpMultiply *= nums[i];
        // tmpMultiply >= k, ">=" very important
        while(tmpMultiply >= k && left <= i) {
            tmpMultiply /= nums[left];
            left++;
        }
        if (tmpMultiply < k) {
            result += (i - left + 1);
        }
    }
    return result;
}

/* 3. Longest Substring Without Repeating Characters */
int lengthOfLongestSubstring(string s) {
    int size = s.size();
    if (size <= 1) {
        return size;
    }
    int left = 0;
    int result = 1;
    std::unordered_map<char, int> myCharMap;
    myCharMap[s[0]] = 1;
    for (int i = 1; i < size; i++) {
        auto iter = myCharMap.find(s[i]);
        if (iter == myCharMap.end() || iter->second == 0) {
            myCharMap[s[i]]++;
            result = std::max(result, i - left + 1);
        } else {
            while(s[left] != s[i]) {
                myCharMap[s[left]]--;
                left++;
            }
            left++;
        }
    }
    return result;
}

/* 2958. Length of Longest Subarray With at Most K Frequency */
int maxSubarrayLength(vector<int>& nums, int k) {
    int size = nums.size();
    int left = 0;
    int result = 0;
    std::unordered_map<int, int> digitMap;
    for (int i = 0; i < size; i++) {
        auto iter = digitMap.find(nums[i]);
        if (iter == digitMap.end() || iter->second < k) {
            digitMap[nums[i]]++;
            result = std::max(result, i - left + 1);
        } else if (iter->second == k) {
            while(nums[left] != nums[i]) {
                digitMap[nums[left]]--;
                left++;
            }
            left++;
        }
    }
    return result;
}

/* 2730. Find the Longest Semi-Repetitive Substring */
int longestSemiRepetitiveSubstring(string s) {
    int size = s.size();
    if (size <= 1) {
        return size;
    }
    int left = 0, result = 0;
    int countPair = 0, preReIndx = -1;
    // do remember to update pre repeat index!!!!!!!!!!!
    for (int i = 1; i < size; i++) {
        if (s[i] != s[i - 1]) {
            result = std::max(result, i - left + 1);
        } else {
            countPair++;
            if (countPair < 2) {
                preReIndx = i - 1;
                result = std::max(result, i - left + 1);
            } else {
                left = preReIndx + 1;
                preReIndx = i - 1;
                countPair--;
            }
        }
    }
    return result;
}

/* 2779. Maximum Beauty of an Array After Applying Operation */
int maximumBeauty(vector<int>& nums, int k) {
    ranges::sort(nums);
    int result = 0;
    int left = 0, size = nums.size();
    for (int i = 0; i < size; i++) {
        int gap = nums[i] - nums[left];
        while(left < i && gap > 2 * k) {
            left++;
            gap = nums[i] - nums[left];
        }
        result = std::max(result, i - left + 1);
    }
    return result;
}

/* 1004. Max Consecutive Ones III */
int longestOnes(vector<int>& nums, int k) {
    int size = nums.size();
    int left = 0, flipCounter = 0, result = 0;
    std::queue<int> indxQ;
    for (int i = 0; i < size; i++) {
        if (nums[i]) {
            result = std::max(result, i - left + 1);
        } else {
            if (k > 0) {
                if (flipCounter < k) {
                    flipCounter++;
                    result = std::max(result, i - left + 1);
                    indxQ.push(i);
                } else {
                    left = indxQ.front() + 1;
                    result = std::max(result, i - left + 1);
                    indxQ.pop();
                    indxQ.push(i);
                }
            } else {
                left = i + 1;
            }
        }
    }
    return result;
}

/* 2962. Count Subarrays Where Max Element Appears at Least K Times */
long long countSubarrays(vector<int>& nums, int k) {
    int size = nums.size();
    if (size < k) return 0;
    int maxValue = nums[0];
    for (int i = 1; i < size; i++) {
        maxValue = maxValue >= nums[i] ? maxValue : nums[i];
    }
    long long result = 0;
    int left = 0, counter = 0;
    for (int i = 0; i < size; i++) {
        counter = (nums[i] == maxValue) ? counter + 1 : counter;
        while(counter == k) {
            counter = (nums[left] == maxValue) ? counter - 1 : counter;
            left++;
        }
        result += left;
    }
    return result;
}

/* 2302. Count Subarrays With Score Less Than K */
long long countSubarrays2(vector<int>& nums, long long k) {
    int size = nums.size();
    if (size <= 1) {
        return (size == 1) ? (nums[0] < k ? 1 : 0) : 0; 
    }
    int left = 0;
    long long tmpSum = 0;
    long long result = 0;
    for (int i = 0; i < size; i++) {
        tmpSum += nums[i];
        while(tmpSum * (i - left + 1) >= k) {
            tmpSum -= nums[left];
            left++;
        }
        result += (i - left + 1); 
    }
    return result;
}

/* 1658. Minimum Operations to Reduce X to Zero */
int minOperations(vector<int>& nums, int x) {
    int size = nums.size();
    if (size == 1) {
        return x == nums[0] ? 1 : -1;
    }
    int accum = std::accumulate(nums.begin(), nums.end(), 0);
    if (accum < x) {
        return -1;
    }
    // do the reverse work, find max subarray that match accum - x;
    int left = 0, target = accum - x;
    int result = -1, tmpSum = 0;
    for (int i = 0; i < size; i++) {
        tmpSum += nums[i];
        while(tmpSum > target) {
            tmpSum -= nums[left];
            left++;
        }
        if (tmpSum == target) {
            result = std::max(result, i - left + 1);
        }
    }
    return result == -1 ? -1 : size - result; 
}

/* 76. Minimum Window Substring */
bool checkCovering(int cntS[], int cntT[]) {
    for (int i = 'a'; i <= 'z'; i++) {
        if (cntS[i] < cntT[i]) {
            return false;
        }
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        if (cntS[i] < cntT[i]) {
            return false;
        }
    }
    return true;
}

string minWindow(string s, string t) {
    std::string result;
    int size = s.size();
    if (size < t.size()) {
        return result;
    }
    int left = 0;
    int indx = -1, minLen = INT32_MAX;
    int cntS[128]{}, cntT[128]{};
    for(char ch : t) {
        cntT[ch]++;
    }
    for (int i = 0; i < size; i++) {
        cntS[s[i]]++;
        while(checkCovering(cntS, cntT)) {
            if (minLen > (i - left + 1)) {
                minLen = (i - left + 1);
                indx = left;
            }
            cntS[s[left]]--;
            left++;
        }
    }
    return indx == -1 ? "" : s.substr(indx, minLen);
}

int main()
{
    std::vector<int> nums = {10,5,2,6};
    std::cout << "713. Subarray Product Less Than K : nums = [10,5,2,6], k = 100 :  " << numSubarrayProductLessThanK(nums, 100) << std::endl;

    string s1 = "abcabcbb";
    std::cout << "3. Longest Substring Without Repeating Characters : abcabcbb : " << lengthOfLongestSubstring(s1) << std::endl;

    std::vector<int> nums1 = {2,1,1,2,3};
    std::cout << "2958. Length of Longest Subarray With at Most K Frequency : 2,1,1,2,3 : " << maxSubarrayLength(nums1, 1) << std::endl;

    std::cout << "2730. Find the Longest Semi-Repetitive Substring : 0001 : " << longestSemiRepetitiveSubstring("0001") << std::endl;
    std::cout << "4411794 : " << longestSemiRepetitiveSubstring("4411794") << std::endl;
    std::cout << "24489929009 : " << longestSemiRepetitiveSubstring("24489929009") << std::endl;

    std::vector<int> nums2 = {4,6,1,2};
    std::cout << "2779. Maximum Beauty of an Array After Applying Operation : nums2 = {4,6,1,2} " << maximumBeauty(nums2, 2) << std::endl;
    // std::vector<int> nums3 = {100000};
    // std::cout << "2779. Maximum Beauty of an Array After Applying Operation : nums3 = {100000} " << maximumBeauty(nums3, 0) << std::endl;

    std::vector<int> nums3 = {2,1,4,3,5};
    std::cout << "2302. Count Subarrays With Score Less Than K : nums = [2,1,4,3,5], k = 10, Output: " << countSubarrays2(nums3, 10) << std::endl;

    // std::vector<int> nums4 = {1,1,4,2,3};
    // std::cout << "1658. Minimum Operations to Reduce X to Zero : nums = [1,1,4,2,3], x = 5, Output: " << minOperations(nums3, 5) << std::endl;


    return 0;
}