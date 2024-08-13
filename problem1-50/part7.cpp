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

/*  */

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

    return 0;
}
