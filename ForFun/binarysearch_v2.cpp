#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>

using namespace std;

/* 162. Find Peak Element */
int findPeakElement(vector<int>& nums) {
    int left = -1, right = nums.size() - 1;
    while(left + 1 < right) {
        int mid = left + (right- left) / 2;
        if (nums[mid] > nums[mid + 1]) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return right;
}

/* 153. Find Minimum in Rotated Sorted Array */
int findMin(vector<int>& nums) {
    int size = nums.size();
    int left = -1, right = size - 1;
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[size - 1]) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return nums[right];
}

/* 33. Search in Rotated Sorted Array */
int search(vector<int>& nums, int target) {
    int size = nums.size();
    auto check = [&](int mid) -> bool {
        int end = nums[size - 1];
        if (nums[mid] > end) {
            return target > end and nums[mid] >= target;
        } else {
            return target > end or nums[mid] >= target;
        }
    };
    int left = 0, right = size - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (nums[right + 1] != target || right == size - 1) {
        return -1;
    }
    return right + 1;
}

/* 1901. Find a Peak Element II */
int getMaxIndex(vector<int> row) {
    return ranges::max_element(row) - row.begin();
}

vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int left = 0, right = mat.size() - 2;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        int maxIndx = getMaxIndex(mat[mid]);
        if (mat[mid][maxIndx] < mat[mid + 1][maxIndx]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return {left, getMaxIndex(mat[left])};
}


/* 154. Find Minimum in Rotated Sorted Array II */
int findMin2(vector<int>& nums) {
    int size = nums.size();
    int left = -1, right = size - 1;
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            right--;
        }
    }
    return nums[right];
}

int main()
{
    std::vector<int> nums = {1,2,3,1};
    std::cout << "162. Find Peak Element for nums = [1,2,3,1]: " << findPeakElement(nums) << std::endl;

    std::vector<int> nums1 = {2,2,2,0,1};
    std::cout << "154. Find Minimum in Rotated Sorted Array II for nums = [2,2,2,0,1]: " << findMin2(nums1) << std::endl;
    std::vector<int> nums2 = {3,1,3};
    std::cout << "154. Find Minimum in Rotated Sorted Array II for nums = [3,1,3]: " << findMin2(nums2) << std::endl;


    return 0;
}