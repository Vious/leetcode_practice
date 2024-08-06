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
            results.push_back(strTable[idx].substr(i, 0));
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

/* Problem 18. 4Sum */
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    int size = nums.size();
    if (size < 4) {
        return {};
    }
    if (size == 4) {
        if ((nums[0]+nums[1]+nums[2]+nums[3]) == target) {
            return {{nums[0], nums[1], nums[2], nums[3]}};
        } else {
            return {};
        }
    }
    // std::ranges::sort(nums);
    std::sort(nums.begin(), nums.end());
    if ((nums[0]+nums[1]+nums[2]+nums[3]) > target) {
        return {};
    } else if ((nums[size-1]+nums[size-2]+nums[size-3]+nums[size-4]) < target) {
        return {};
    }
    std::vector<std::vector<int>> results;
    for (int i = 0; i < size - 3; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        int wanted1 = target - nums[i];
        for (int j = i + 1; j < size - 2; j++) {
            // important!!! check j > i + 1
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            int left = j + 1;
            int right = size - 1;
            int wanted2 = wanted1 - nums[j];
            while(left < right) {
                int tmpSum = nums[left] + nums[right];
                if (tmpSum == wanted2) {
                    results.push_back({nums[i], nums[j], nums[left], nums[right]});
                    left++;
                    while(nums[left] == nums[left-1] && left < right) left++;
                    right--;
                    while(nums[right] == nums[right+1] && right > left) right--;
                } else if (tmpSum > wanted2) {
                    right--;
                } else {
                    left++;
                }
            }
        }
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

    std::cout << "Testing for Problem 18. 4Sum: " << std::endl;
    std::vector<int> testCase1P18 = {-2,-1,-1,1,1,2,2};
    std::vector<int> testCase2P18 = {2,0,3,0,1,2,4};
    auto results = fourSum(testCase1P18, 0);
    for (auto res : results) {
        std::cout << "Results: ";
        for (auto ele : res) {
            std::cout << ele << " ";
        }
        std::cout << "\n";
    }
    auto results2 = fourSum(testCase2P18, 7);
    for (auto res : results2) {
        std::cout << "Results: ";
        for (auto ele : res) {
            std::cout << ele << " ";
        }
        std::cout << "\n";
    }

    return 0;
}