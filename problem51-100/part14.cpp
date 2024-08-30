#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>

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

/*  */

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

    return 0;
}