#include <iostream>
#include <vector>
#include <string>
#include <cstring>

/* 713. Subarray Product Less Than K */
int numSubarrayProductLessThanK(std::vector<int>& nums, int k) {
    if (k <= 1) {
        return 0;
    }
    int res = 0;
    int left = 0, prod = 1, size = nums.size();
    for (int right = 0; right < size; right++) {
        prod *= nums[right];
        while(prod >= k) {
            prod /= nums[left];
            left++;
        }
        res += (right - left + 1);
    }
    return res;
}


int main()
{
    std::cout << "Test 713. Subarray Product Less Than K " << std::endl;
    std::vector<int> nums = {10, 5, 2, 6};
    std::cout << "Test nums = {10, 5, 2, 6}, k = 100 : " << numSubarrayProductLessThanK(nums, 100) << std::endl; 

    return 0;
}