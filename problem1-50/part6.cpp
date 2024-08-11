#include <iostream>
#include <vector>

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

    

    return 0;
}