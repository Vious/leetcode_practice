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

/* 2300. Successful Pairs of Spells and Potions */
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
    int M = spells.size(), N = potions.size();
    ranges::sort(potions);
    std::vector<int> results;
    for (int value : spells) {
        int left = 0, right = N - 1;
        int mid;
        while(left <= right) {
            mid = left + (right - left) / 2;
            long long multiRes = (long long) potions[mid] * value;
            if (multiRes >= success) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (left >= N) {
            results.push_back(0);
        } else if (right < 0) {
            results.push_back(N);
        } else {
            results.push_back(N - right - 1);
        }
    }
    return results;
}

/* 2563. Count the Number of Fair Pairs */
long long countFairPairs(vector<int>& nums, int lower, int upper) {
    /* brute-force */
/*     // int size = nums.size();
    // long long result = 0;
    // for (int i = 0; i < size; i++) {
    //     for (int j = i + 1; j < size; j++) {
    //         long long sum = nums[i] + nums[j];
    //         if (sum >= lower && sum <= upper) {
    //             result++;
    //         }
    //     }
    // }
    // return result;
 */    
    ranges::sort(nums);
    int size = nums.size();
    if (size <= 1) {
        return 0;
    }
    long long result = 0;
    int lowIndx, upIndx;
    for (int i = 0; i < size; i++) {
        int left = i + 1, right = size - 1;
        int mid;
        while(left <= right) {
            mid = left + (right - left) / 2;
            long long sum = nums[i] + nums[mid];
            if (sum >= lower) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        lowIndx = left;
        left = i + 1, right = size - 1;
        while(left <= right) {
            mid = left + (right - left) / 2;
            long long sum = nums[i] + nums[mid];
            if (sum <= upper) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        upIndx = left;
        if (lowIndx < size && lowIndx < upIndx && upIndx > 0) {
            if (lowIndx <= i && upIndx >= i) {
                result += (upIndx - lowIndx - 1);
            } else {
                result += (upIndx - lowIndx);
            }
        } 
    }
    return result;
}

/* 275. H-Index II */
int hIndex(vector<int>& citations) {
    int size = citations.size();
    int result = 0;
    int left = 0, right = size - 1;
    int mid;
    if (citations[left] >= size) {
        return size;
    }
    while(left <= right) {
        mid = left + (right - left) / 2;
        if (citations[mid] >= (size - mid)) {
            result = std::max(result, size - mid);
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

/*  */

int main()
{
    std::vector<int> spells = {5, 1, 3}, potions = {1, 2, 3, 4, 5};
    std::cout << "2300. Successful Pairs of Spells and Potions, spells = [5,1,3], potions = [1,2,3,4,5], success = 7 : ";
    auto res = successfulPairs(spells, potions, 7);
    for (auto ele : res) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
    
    // std::vector<int> spells1 = {3, 1, 2}, potions1 = {8, 5, 8};
    // std::cout << "spells = {3, 1, 2}, potions = {8, 5, 8}, success = 16 : ";
    // auto res1 = successfulPairs(spells1, potions1, 16);
    // for (auto ele : res1) {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "275. H-Index II, : ";


    return 0;
}