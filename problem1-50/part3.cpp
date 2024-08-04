#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

/* Problem 11. (Container With Most Water) */
int maxArea(std::vector<int>& height) {
    int size = height.size();
    if (size <= 1) {
        return 0;
    }
    int left = 0, right = size - 1;
    int maxResult = (right - left) * std::min(height[left], height[right]);
    int tmpResult;
    while(left < right) {
        if(height[right] >= height[left]) {
            left++;
        } else {
            right--;
        }
        tmpResult = (right - left) * std::min(height[left], height[right]);
        maxResult = tmpResult > maxResult? tmpResult : maxResult;
    }

    return maxResult;
}

/* Problem 12. Integer to Roman */
static std::vector<std::vector<std::string>> romansTable = {
    {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"M", "MM", "MMM"}
};
std::string intToRoman(int num) {
    std::string results("");
    // first solution, use the above roman number table
    while(num) {
        if (num >= 1000) {
            results += romansTable[3][num / 1000 - 1];
            num = num - (num / 1000) * 1000; 
        } else if (num >= 100) {
            results += romansTable[2][num / 100 - 1];
            num = num - (num / 100) * 100;
        } else if (num >= 10) {
            results += romansTable[1][num / 10 - 1];
            num = num - (num / 10) * 10;
        } else if (num >= 1) {
            results += romansTable[0][num - 1];
            num = 0;
        }
    }
    return results;
}

/* Problem 13. Roman to Integer*/
static std::unordered_map<char, int> rom2IntMap = {
    {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
    {'C', 100}, {'D', 500}, {'M', 1000}
};
int romanToInt(std::string s){
    int size = s.size();
    int resultNum = 0;
    for (int i = 0; i < size; i++) {
        if (i < size - 1) {
            if (rom2IntMap[s[i]] < rom2IntMap[s[i+1]]) {
                resultNum += rom2IntMap[s[i+1]] - rom2IntMap[s[i]];
                i++; // important!!!
            } else {
                resultNum += rom2IntMap[s[i]];
            }
        } else {
            resultNum += rom2IntMap[s[i]];
        }
    }
    return resultNum;
}

/* Problem 14. Longest Common Prefix*/
std::string longestCommonPrefix(std::vector<std::string>& strs) {
    int arrNumber = strs.size();
    if (arrNumber == 0) return "";
    // std::string result = ""; used by solution 1
    int shortestNum = strs[0].size();
    // find the shortest string size
    for (int i = 1; i < arrNumber; i++) {
        shortestNum = std::min(shortestNum, (int)strs[i].size());
    }
    bool flag;
    // solution 1
/*     for (int i = 0; i < shortestNum; i++) {
        flag = true;
        char tmpStr = strs[0][i];
        for (int j = 1; j < arrNumber; j++) {
            if (strs[j][i] != tmpStr) {
                flag = false;
                break;
            }
        }
        if (flag) {
            result += tmpStr;
        } else {
            break;
        }
    }
    return result;
 */    
    // solution 2:
    int endIdx = -1;
    for (int i = 0; i < shortestNum; i++) {
        flag = true;
        char tmpStr = strs[0][i];
        for (int j = 1; j < arrNumber; j++) {
            if (strs[j][i] != tmpStr) {
                flag = false;
                break;
            }
        }
        if (flag) {
            endIdx++;
        } else {
            break;
        }
    }
    return endIdx >= 0 ? strs[0].substr(0, endIdx + 1) : "";
}

/* Problem 15. 3Sum */
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    int size = nums.size();
    if (size == 3) {
        if (nums[0] + nums[1] + nums[2] == 0) {
            return {{nums[0], nums[1], nums[2]}};
        } else {
            return {};
        }
    }
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> results;
    int left, right;
    for (int i = 0; i < size - 2; i++) {
        if (i != 0 && nums[i] == nums[i-1]) continue;

        left = i + 1;
        right = size - 1;
        int wanted = -nums[i];
        while(left < right) {
            int tmpSum = nums[left] + nums[right];
            if (tmpSum == wanted) {
                results.push_back({nums[i], nums[left], nums[right]});
                left++;
                while(nums[left] == nums[left-1] && left < right) left++;
                right--;
                while(nums[right] == nums[right+1] && right > left) right--;
            } else if (tmpSum > wanted) {
                right--;
            } else {
                left++;
            }
        }
    }
    
    return results;
}

int main()
{
    std::cout << "Testing for Problem 11. (Container With Most Water): " << std::endl;
    std::vector<int> heights1 = {1,8,6,2,5,4,8,3,7};
    std::cout << "heights1 = {1,8,6,2,5,4,8,3,7}," << " maxArea: " << maxArea(heights1) << std::endl;
    std::vector<int> heights2 = {1,1};
    std::cout << "heights2 = {1,1}," << " maxArea: " << maxArea(heights2) << std::endl;

    std::cout << "Testing for Problem 12. Integer to Roman: " << std::endl;
    std::cout << "Input: 3749" << ", Expected: " << "MMMDCCXLIX" << " , Output: " << intToRoman(3749) << std::endl;

    std::cout << "Testing for Problem 13. Roman to Integer: " << std::endl;
    std::cout << "Input: MCMXCIV" << ", Expected: " << "1994" << " , Output: " << romanToInt("MCMXCIV") << std::endl;

    std::cout << "Testing for Problem 14. Longest Common Prefix: " << std::endl;

    std::vector<std::string> strs = {"flower","flow","flight"};
    std::cout << "Common prefix: " << longestCommonPrefix(strs) << std::endl;

    std::cout << "Testing for Problem 15. 3Sum: " << std::endl;
    std::vector<int> case1 = {1,2,-2,-1};
    std::vector<std::vector<int>> res = threeSum(case1);
    for (auto &vec : res) {
        for (auto ele :vec ) {
            std::cout << ele << " " << std::endl;
        }
    }

    return 0;
}