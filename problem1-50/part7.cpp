#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <cstring>

/* 31. Next Permutation */
void nextPermutation(std::vector<int>& nums) {
    int size = nums.size();
    if (size <= 1) {
        return;
    } else if (size == 2) {
        std::swap(nums[0], nums[1]);
        return;
    }
    // just for fun, the simplest way, lol.
    // std::next_permutation(nums.begin(), nums.end());
    int right = size - 2;
    while(right >= 0 && nums[right] >= nums[right + 1]) {
        right--;
    }
    if (right >= 0) {
        int swapIdx = size - 1;
        while(swapIdx >= 0 && nums[swapIdx] <= nums[right]) {
            swapIdx--;
        }
        std::swap(nums[right], nums[swapIdx]);
    }
    std::reverse(nums.begin() + right + 1, nums.end());
}

/* 32. Longest Valid Parentheses */
int longestValidParentheses(std::string s) {
    int size = s.size();
    if (size <= 1) {
        return 0;
    } else if (size == 2 && (s[0] != '(' || s[1] != ')') ) {
        return 0;
    }
    // int dp[size + 1] = {0}; // may face "variable-sized object may not be initialized" on leetcode server
    int dp[size + 1];
    memset(dp, 0, (size + 1) * sizeof(int));
    int validNum = 0;
    for (int i = 1; i < size; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = dp[i - 2] + 2;
            } else {
                if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                    if (i - dp[i - 1] - 2 >= 0) {
                        dp[i] = dp[i - 1] + 2 + dp[i - dp[i - 1] - 2];
                    } else {
                        dp[i] = dp[i - 1] + 2;
                    }
                }
            }
        } 
        validNum = std::max(validNum, dp[i]);
    }
    return validNum;
}

/* 33. Search in Rotated Sorted Array */
int search(std::vector<int>& nums, int target) {
    int size = nums.size();
    if (size == 0 || (size == 1 && nums[0] != target)) {
        return -1;
    }
    int left = 0, right = size - 1;
    if (target < nums[left] && target > nums[right]) {
        return -1;
    }
    int middle;
    while(left <= right) { 
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            return middle;
        } else if (nums[middle] > target) {
            if (nums[middle] > nums[right]) {
                if(target > nums[right]) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                } 
            } else {
                right = middle - 1;
            }
        } else {
            if (nums[middle] > nums[right]) {
                left = middle + 1;
            } else {
                if (target > nums[right]) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            }
        }
    }
    return -1;
}

/* 34. Find First and Last Position of Element in Sorted Array */
std::vector<int> searchRange(std::vector<int>& nums, int target) {
    int size = nums.size();
    if (size < 1) {
        return {-1, -1};
    }
    int left = 0, right = size - 1;
    int middle;
    while(left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            int mLeft = middle, mRight = middle;
            while(mLeft > 0 && nums[mLeft] == target) {
                mLeft--;
            }
            mLeft = nums[mLeft] == target ? mLeft : mLeft + 1;
            while(mRight < size - 1 && nums[mRight] == target) {
                mRight++;
            }
            mRight = nums[mRight] == target ? mRight : mRight - 1;
            return {mLeft, mRight};
        } else if (nums[middle] > target) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return {-1, -1};
}

/* 35. Search Insert Position */
int searchInsert(std::vector<int>& nums, int target) {
    int size = nums.size();
    if (size < 1) {
        return 0;
    }
    if (size == 1) {
        return nums[0] >= target ? 0 : 1;
    }
    int left = 0, right = size - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            return middle;
        } else if (nums[middle] > target) {
            if (middle == 0) {
                return 0;
            } else if (middle >= 1 && nums[middle - 1] < target) {
                return middle;
            }
            right = middle - 1;
        } else {
            if (middle == size - 1) {
                return size;
            } else if (middle < size - 1 && nums[middle + 1] > target) {
                return middle + 1;
            }
            left = middle + 1;
        }
    }
    return left;
    // or more simpler way
    // int left = 0, right = size - 1;
    // int middle;
    // while (left <= right) {
    //     middle = (left + right) / 2;
    //     if (nums[middle] == target) {
    //         return middle;
    //     } else if (nums[middle] > target) {
    //         right = middle - 1;
    //     } else {
    //         left = middle + 1;
    //     }
    // }
    // return left;
}

int main()
{
    std::cout << "Testing for Problem 31. Next Permutation: " << std::endl;
    std::vector<int> nums = {1,3,2};
    nextPermutation(nums);
    for (auto &num : nums) {
        std::cout << num << ", "; 
    }
    std::cout << std::endl;

    std::cout << "Testing for Problem 32. Longest Valid Parentheses: " << std::endl;
    std::cout << "Test for case (()()) : " << longestValidParentheses("(()())") << std::endl;

    std::cout << "Testing for Problem 33. Search in Rotated Sorted Array: " << std::endl;
    std::vector<int> testCase = {4,5,6,7,0,1,2};
    std::cout << "Case : nums = [4,5,6,7,0,1,2], target = 0, " << " Output: " << search(testCase, 0) << std::endl;

    std::cout << "Testing for Problem 34. Find First and Last Position of Element in Sorted Array: " << std::endl;
    std::vector<int> testCase2 = {5,7,7,8,8,10};
    std::cout << "Case : nums = [5,7,7,8,8,10], target = 8, " << " Output: ";
    auto res = searchRange(testCase2, 8);
    for (auto &ele : res) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
    std::cout << "Case : nums = [5,7,7,8,8,10], target = 8, " << " Output: " << searchInsert(testCase2, 8) << std::endl;



    return 0;
}
