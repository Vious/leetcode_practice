#include <iostream>
#include <vector>
#include <cmath>

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

int main()
{
    std::cout << "Testing for Problem 11. (Container With Most Water): " << std::endl;
    std::vector<int> heights1 = {1,8,6,2,5,4,8,3,7};
    std::cout << "heights1 = {1,8,6,2,5,4,8,3,7}," << " maxArea: " << maxArea(heights1) << std::endl;
    std::vector<int> heights2 = {1,1};
    std::cout << "heights2 = {1,1}," << " maxArea: " << maxArea(heights2) << std::endl;

    return 0;
}