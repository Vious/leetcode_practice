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


/* 43. Multiply Strings */


int main()
{
    std::cout << "Testing for Problem 41. (First Missing Positive) : " << std::endl;


    return 0;
}