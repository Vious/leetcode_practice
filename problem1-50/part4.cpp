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

int main()
{
    std::cout << "Testing for Problem 16. 3Sum Closest: " << std::endl;
    std::vector<int> test1 = {-1,2,1,-4};
    std::cout << "Input [-1,2,1,-4] " << ", Output: " << threeSumClosest(test1, 1) << std::endl;

    return 0;
}