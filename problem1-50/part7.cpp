#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    return 0;
}
