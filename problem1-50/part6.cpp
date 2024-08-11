#include <iostream>
#include <vector>
#include <string>

/* 26. Remove Duplicates from Sorted Array */
int removeDuplicates(std::vector<int>& nums) {
    int size = nums.size();
    if (size <= 1) {
        return size;
    }
    // a very simple solution
    // just check the nums[i] == nums[i - 1] or not
    // int uniqueNum = 1;
    // for (int i = 1; i < size; i++) {
    //     if (nums[i] != nums[i - 1]) {
    //         nums[uniqueNum] = nums[i];
    //         uniqueNum++;
    //     }
    // } 
    // return uniqueNum;
    // two pointers
    int uniqueNum = 1;
    int left = 0, right = 1;
    while(right < size && left < right) {
        while(right < size && nums[right] == nums[left]) {
            right++;
        }
        if (right == size) {
            break;
        } else {
            nums[uniqueNum] = nums[right];
            left = right;
            right = left + 1;
            uniqueNum++;
        }
    }

    return uniqueNum;
}

/* 27. Remove Element */
int removeElement(std::vector<int>& nums, int val) {
    int size = nums.size();
    if (size == 0 || (size == 1 && nums[0] == val)) {
        return 0;
    } 
    int rmIdx = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] != val) {
            nums[rmIdx] = nums[i];
            rmIdx++;
        }
    }

    return rmIdx;
}

 /* 28. Find the Index of the First Occurrence in a String */
int strStr(std::string haystack, std::string needle) {
    int size1 = haystack.size(), size2 = needle.size();
    if (size2 > size1 || size1 == 0) {
        return -1;
    }
    auto idx = haystack.find(needle);
    return idx != std::string::npos ? idx : -1;
}

/* 29. Divide Two Integers */
int divide(int dividend, int divisor) {
    if (dividend == divisor) {
        return 1;
    }
    int sign1 = dividend & 0x80000000, sign2 = divisor & 0x80000000;
    int sign = ((sign1) ^ (sign2));
    unsigned int absDividend = abs(dividend);
    unsigned int absDivisor = abs(divisor);
    unsigned int res = 0;
    while(absDividend >= absDivisor) {
        short q = 0;
        while(absDividend > (absDivisor << (q + 1))) {
            q++;
        }
        absDividend -= (absDivisor << q);
        res += (1 << q);
    }
    // check if it can be represented as 32-bit int
    if ((res & 0x80000000) && !sign) {
        return INT32_MAX;
    }
    return sign ? -res : res;
}

/*  */


int main()
{
    std::cout << "Testing for Problem 26. Remove Duplicates from Sorted Array: " << std::endl;
    std::vector<int> nums = {1,1,2,3};
    // pay attention to case :[1,1,2,3]
    std::cout << "Unique number : " << removeDuplicates(nums) << std::endl;
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Testing for Problem 27. Remove Element: " << std::endl;
    std::vector<int> nums2 = {0,1,2,2,3,0,4,2};
    std::cout << "Remaining number : " << removeElement(nums2, 2) << std::endl;
    for (auto num : nums2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Testing for Problem 28. Find the Index of the First Occurrence in a String: " << std::endl;
    std::cout << "Test for haystack = \"leetcode\", needle = \"leeto\": " << strStr("leetcode", "leeto") << std::endl;

    std::cout << "Testing for Problem 29. Divide Two Integers: " << std::endl;
    std::cout << "dividend = -2147483648, divisor = -1 : " << divide(-2147483648, -1) << std::endl;



    return 0;
}