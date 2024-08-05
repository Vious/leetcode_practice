#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ranges>

/* Problem 16. 3Sum Closest */
int threeSumClosest(std::vector<int>& nums, int target) {
     int size = nums.size();
     if (size == 3) {
        return nums[0]+nums[1]+nums[2];
     }
     std::sort(nums.begin(), nums.end());
    //  ranges::sort(nums);
     // the specicial cases
     if (nums[0]+nums[1]+nums[2] > target) return nums[0]+nums[1]+nums[2];
     if (nums[size-1]+nums[size-2]+nums[size-3] < target) return nums[size-1]+nums[size-2]+nums[size-3];
     int result = nums[0]+nums[1]+nums[2];
     int left, right;
     for (int i = 0; i < size - 2; i++) {
        left = i + 1;
        right = size - 1;
        while(left < right) {
            int tmpSum = nums[i] + nums[left] + nums[right];
            if (tmpSum == target) {
                return target;
            } else if (tmpSum > target) {
                if (std::abs(tmpSum - target) < std::abs(result - target)){
                    result = tmpSum;
                }
                right--;
            } else {
                if (std::abs(tmpSum - target) < std::abs(result - target)){
                    result = tmpSum;
                }
                left++;
            }
        }
     }

     return result;
}

/* Problem 17. Letter Combinations of a Phone Number */
static std::vector<std::string> strTable = {
    "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

void backtrace(std::string curCombination, std::string nextDigits, std::vector<std::string> &results) {
    if (nextDigits.size() == 0) {
        results.push_back(curCombination);
    } else {
        int idx = nextDigits[0] - '2';
        auto tmpStr = strTable[idx];
        for (auto str : tmpStr) {
            backtrace(curCombination + str, nextDigits.substr(1), results);
        }

    }
}

std::vector<std::string> letterCombinations(std::string digits) {
    int size = digits.size();
    if (size == 0) return {};
    if (size == 1) {
        std::vector<std::string> results;
        int idx = digits[0] - '2';
        for (int i = 0; i < strTable[idx].size(); i++) {
            std::string tmpCh = "";
            tmpCh = strTable[idx][i];
            results.push_back(tmpCh);
        }
        return results;
    }
    std::vector<std::string> results{""};

    // solution 1, recursive
    // backtrace("", digits, results);
    // return results;
    // solution 2, iterative
    for (char aDigit : digits) {
        int idx = aDigit - '2';
        std::vector<std::string> tmpStrs;
        for (auto tmpComb : results) {
            for (char aChar : strTable[idx]) {
                tmpStrs.push_back(tmpComb + aChar);
            }
        }
        results = std::move(tmpStrs);
    }
    return results;
}

int main()
{
    std::cout << "Testing for Problem 16. 3Sum Closest: " << std::endl;
    std::vector<int> test1 = {-1,2,1,-4};
    std::cout << "Input [-1,2,1,-4] " << ", Output: " << threeSumClosest(test1, 1) << std::endl;

    std::cout << "Testing for Problem 17. Letter Combinations of a Phone Number: " << std::endl;
    std::cout << "Test case: \"23\"" << ", Output:";
    auto result = letterCombinations("23");
    for (auto str : result) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}