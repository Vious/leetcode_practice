#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>


using namespace std;

/* 34. Find First and Last Position of Element in Sorted Array */
vector<int> searchRange(vector<int>& nums, int target) {
    int size = nums.size();
    if (size < 1) {
        return {-1, -1};
    } else if (size == 1) {
        if (nums[0] == target) {
            return {0, 0};
        } else {
            return {-1, -1};
        }
    }

    int left = 0, right = size - 1;
    int mid;
    while(left <= right) {
        // take care of overflow
        /* mid = left + (right - left) / 2 */
        mid = left + (right - left) / 2;
        if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            left = right = mid;
            while(left >= 0 && nums[left] == target) {
                left--;
            }
            while(right <= size - 1 && nums[right] == target) {
                right++;
            }
            return {left + 1, right - 1};
        }
    }
    return {-1, -1};
}


/* 2529. Maximum Count of Positive Integer and Negative Integer */
int maximumCount(vector<int>& nums) {
    int size = nums.size();
    if (size == 1) {
        return nums[0] == 0 ? 0 : 1;
    }
    int cntPos = 0, cntNeg = 0;
    int left = 0, right = size - 1;
    int mid = 0;
    while(left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] >= 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
            cntNeg = left;
        }
    }
    left = mid, right = size - 1;
    while(left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] <= 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
            cntPos = size - right - 1;
        }
    }
    return std::max(cntNeg, cntPos); 
}

int main()
{
    

    return 0;
}