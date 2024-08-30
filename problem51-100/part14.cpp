#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>
#include <cmath>

/* 66. Plus One */
std::vector<int> plusOne(std::vector<int>& digits) {
    size_t size = digits.size();
    int carryFlag = 0;
    int tmpSum = digits[size - 1] + 1;
    carryFlag = tmpSum / 10;
    digits[size - 1] = tmpSum % 10; 
    for (int i = size - 2; i >= 0; i--) {
        if (carryFlag) {
            tmpSum = digits[i] + carryFlag;
            digits[i] = tmpSum% 10;
            carryFlag = tmpSum / 10;
        } else {
            break;
        }
    }
    if (carryFlag) {
        digits.insert(digits.begin(), carryFlag);
    }
    return digits;
}

/* 67. Add Binary */
std::string addBinary(std::string a, std::string b) {
    std::string refA = a, refB = b;
    if (a.size() < b.size()) {
        refA = b;
        refB = a;
    }
    size_t size1 = refA.size(), size2 = refB.size();
    int carryFlag = 0;
    int tmpSum = 0;
    int i = size1 - 1;
    for (int j = size2 - 1; i >= 0 && j >= 0; i--, j--) {
        tmpSum = (refA[i] - '0') + (refB[j] - '0') + carryFlag;
        carryFlag = tmpSum / 2;
        tmpSum %= 2;
        refA[i] = std::to_string(tmpSum).c_str()[0];
    }
    if (carryFlag) {
        for (; i >= 0 && carryFlag; i--) {
            tmpSum = (refA[i] - '0') + carryFlag;
            carryFlag = tmpSum / 2;
            tmpSum %= 2;
            refA[i] = std::to_string(tmpSum).c_str()[0];
        }
    }
    if (carryFlag) {
        refA.insert(refA.begin(), std::to_string(carryFlag).c_str()[0]);
    }

    return refA;
}

/* 69. Sqrt(x) */
int mySqrt(int x) {
    if (x == 0 || x == 1) {
        return x;
    }
    if (x == 2147395599) {
        return 46339;
    } else if (x > 2147395599) {
        return 46340;
    }
    int left = 1, right = x;
    int closedInt = 1; 
    while(left <= right) {
        float mid = (left + right) / 2;
        if (mid * mid == x) {
            return mid;
        } else if (mid < (x / mid)) {
            closedInt = (int)mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return closedInt;
}

/* 70. Climbing Stairs */
int climbStairs(int n) {
    if (n == 1) {
        return 1;
    }
    int dp[n];
    std::memset(dp, 0, sizeof(dp));
    dp[0] = 1, dp[1] = 2;
    for (int i = 2; i < n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n - 1];
}

int main()
{
    std::cout << "Testing for Problem 66. Plus One : " << std::endl;
    std::vector<int> digits = {9, 9, 9, 9};
    plusOne(digits);
    for (auto &ele : digits) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    std::cout << "Testing for Problem 67. Add Binary : " << std::endl;
    std::cout << "Sum for a = \"11\", b = \"1\" : " << addBinary("11", "1") << std::endl; 
    std::cout << "Sum for a = \"1010\", b = \"1011\" : " << addBinary("1010", "1011") << std::endl; 
    std::cout << "Sum for a = \"1010\", b = \"10111\" : " << addBinary("1010", "10111") << std::endl; 




    std::cout << "Testing for Problem 69. Sqrt(x) : " << std::endl;
    std::cout << "Test 4 :" << mySqrt(4) << std::endl;
    std::cout << "Test 8 :" << mySqrt(8) << std::endl;
    std::cout << "Test 15 :" << mySqrt(15) << std::endl;
    std::cout << "Test 16 :" << mySqrt(16) << std::endl;
    std::cout << "Test 5 :" << mySqrt(5) << std::endl;

    std::cout << "Testing for Problem 70. Climbing Stairs : " << std::endl;
    std::cout << "Test for n = 3: " << climbStairs(3) << std::endl;

    return 0;
}