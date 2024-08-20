#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cstring>

/* Problem 41. (First Missing Positive) */
int firstMissingPositive(std::vector<int>& nums) {
    // solutio 1, use hash map or boolean array, very slow. DO NOT meet the requirements.
    // // std::unordered_map<int, int> hashMap;
    // int size = nums.size();
    // if (size == 1) {
    //     return nums[0] == 1 ? 2 : 1; 
    // }
    // std::vector<bool> seen(size + 1, false);
    // int minValue = INT32_MAX;
    // for (int i = 0; i < size; i++) {
    //     if(nums[i] <= 0) {
    //         continue;
    //     }
    //     minValue = std::min(minValue, nums[i]);
    //     // hashMap[nums[i]]++;
    //     if (nums[i] > 0 && nums[i] <= size) {
    //         seen[nums[i]] = true;
    //     }
    // }
    // if (minValue >= 2) {
    //     return 1;
    // }
    // for (int i = 1; i <= size; i++) {
    //     // if (!hashMap[i]) {
    //     //     return i;
    //     // }
    //     if (!seen[i]) {
    //         return i;
    //     }
    // }
    // return size + 1;

    // solution 2
    int size = nums.size();
    if (size == 1) {
        return nums[0] == 1 ? 2 : 1; 
    }
    int pivot = 0;
    while(pivot < size) {
        if (nums[pivot] > 0 && nums[pivot] <= size && nums[pivot] != nums[nums[pivot] - 1]) {
            std::swap(nums[pivot], nums[nums[pivot] - 1]);
        } else {
            pivot++;
        }
    }

    for (int i = 0; i < size; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return size + 1;

}

/* 42. Trapping Rain Water */
int trap(std::vector<int>& height) {
    size_t size = height.size();
    int left = 0, right = size - 1;
    int leftMax = 0, rightMax = 0;
    int result = 0;
    while(left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                result += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                result += rightMax - height[right];
            }
            right--;
        }
    }
    return result;
}

/* 43. Multiply Strings */
std::string twoStrSum(std::string num1, std::string num2) {
    int size1 = num1.size(), size2 = num2.size();
    if (size1 == 0 || size2 == 0) {
        return (size1 == 0) ? num2 : num1;
    }
    int carryValue = 0;
    std::string result = "";
    while(size1 >= 1 && size2 >= 1) {
        int tmpSumValue = (num1[size1-1] - '0') + (num2[size2-1] - '0') + carryValue;
        carryValue = tmpSumValue / 10;
        // result.insert(0, 1, tmpSumValue % 10 + '0');
        result += (tmpSumValue % 10 + '0');
        size1--;
        size2--;
    }
    while(size1 >= 1 ) {
        int tmpSumValue = (num1[size1-1] - '0') + carryValue;
        carryValue = tmpSumValue / 10;
        // result.insert(0, 1, tmpSumValue % 10 + '0');
        result += (tmpSumValue % 10 + '0');
        size1--;
    }
    while(size2 >= 1 ) {
        int tmpSumValue = (num2[size2-1] - '0') + carryValue;
        carryValue = tmpSumValue / 10;
        // result.insert(0, 1, tmpSumValue % 10 + '0');
        result += (tmpSumValue % 10 + '0');
        size2--;
    }
    if(carryValue) {
        // result.insert(0, 1, carryValue + '0');
        result += (carryValue + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;

}

std::string simpleStrMultiply(std::string &num1, int multiplyer, int scale) {
    int size = num1.size() - 1;
    int carryValue = 0;
    std::string result = "";
    while(size >= 0) {
        int tmpValue = (num1[size] - '0') * multiplyer + carryValue;
        carryValue = tmpValue / 10;
        // result.insert(0, 1, tmpValue % 10 + '0');
        result += (tmpValue % 10 + '0');
        size--;
    }
    if(carryValue) {
        // result.insert(0, 1, carryValue + '0');
        result += (carryValue + '0');
    }
    std::reverse(result.begin(), result.end());
    while(scale) {
        int tmpSize = result.size();
        // result.insert(tmpSize, 1, '0');
        result += "0";
        scale--;
    }
    return result;
}

std::string multiply(std::string num1, std::string num2) {
    int size1 = num1.size(), size2 = num2.size();
    if (size1 < size2) {
        std::swap(num1, num2);
    }
    //check for "0" * any number
    if (num2.size() == 1 && num2[0] == '0') {
        return "0";
    } 
    std::string result = "";
    int scale = 0;
    for (int i = num2.size() - 1; i >= 0; i--) {
        result = std::move(twoStrSum(result, simpleStrMultiply(num1, num2[i] - '0', scale)));
        scale++;
    }
    return result;
}

int main()
{
    std::cout << "Testing for Problem 41. (First Missing Positive) : " << std::endl;
    std::vector<int> nums = {3,4,-1,1};
    std::cout << "Smallest positive of nums = {3,4,-1,1} is : " << firstMissingPositive(nums) << std::endl;

    std::cout << "Testing for Problem 42. (Trapping Rain Water) : " << std::endl;
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "How much water it can trap of height = {0,1,0,2,1,0,1,3,2,1,2,1} is : " << trap(height) << std::endl;

    std::cout << "Testing for Problem 43. Multiply Strings : " << std::endl;
    std::cout << "Multiply 123 with 456 = : " << multiply("123", "456") << std::endl;
    std::cout << "Multiply 2 with 3 = : " << multiply("2", "3") << std::endl;

    

    return 0;
}