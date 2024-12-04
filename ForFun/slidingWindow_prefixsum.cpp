#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>


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
    std::vector<int> nums3 = {100000};
    std::cout << "2779. Maximum Beauty of an Array After Applying Operation : nums3 = {100000} " << maximumBeauty(nums3, 0) << std::endl;

    return 0;
}