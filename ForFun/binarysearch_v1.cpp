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

/* 875. Koko Eating Bananas */
bool canEat(vector<int>& piles, int h, int k) {
    int sum = piles.size();
    for (int val : piles) {
        sum += (val - 1) / k;
        if (sum > h) {
            return false;
        }
    }
    return true;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int size = piles.size();
    int left = 1, right = ranges::max(piles);
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (canEat(piles, h, mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return right + 1;
}

/* 2187. Minimum Time to Complete Trips */
bool canComplete(vector<int>& time, int totalTrips, long long curTime) {
    long long sum = 0;
    for (int t : time) {
        sum += (curTime) / t;
        if (sum >= totalTrips) {
            return true;
        }
    }
    return false;
}

long long minimumTime(vector<int>& time, int totalTrips) {
    int size = time.size();
    /* reduce search space */
    auto [minBus, maxBus] = ranges::minmax(time);
    int average = (totalTrips - 1) / size + 1;
    long long left = (long long)minBus * average;
    long long right = std::min((long long)maxBus * average, (long long)minBus * totalTrips);
    while(left <= right) {
        long long mid = left + (right - left) / 2;
        if (canComplete(time, totalTrips, mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return right + 1;
}

/* 2861. Maximum Number of Alloys */
int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
    int result = 0;
    int mx = ranges::min(stock) + budget;
    for (auto &comp : composition) {
        auto canMake = [&] (long long num) -> bool {
            long long tmpSum = 0;
            for (int i = 0; i < n; i++) {
                if (stock[i] < comp[i] * num) {
                    tmpSum += (comp[i] * num - stock[i]) * cost[i];
                    if (tmpSum > budget) {
                        return false;
                    }
                }
            }
            return true;
        };
        int left = result, right = mx + 1;
        while(left <= right) {
            int mid = left + (right - left ) / 2;
            if (canMake(mid)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        result = std::max(result, left - 1);
    }
    return result;
}

/* 2439. Minimize Maximum of Array */
bool isRightLimit(vector<int>& nums, int limit) {
    long long extra = 0;
    for (int i = nums.size() - 1; i > 0; i--) {
        extra = std::max(extra + nums[i] - limit, 0ll);
    }
    return nums[0] + extra <= limit;
}
int minimizeArrayValue(vector<int>& nums) {
    int left = 0, right = ranges::max(nums);
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (isRightLimit(nums, mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return right + 1;
}

/* 2517. Maximum Tastiness of Candy Basket */
int maximumTastiness(vector<int>& price, int k) {
    ranges::sort(price);
    auto checkDistance = [&](int dist) -> int {
        int cnt = 1, pre = price[0];
        for (int p : price) {
            if (p >= pre + dist) {
                cnt++;
                pre = p;
            }
        }
        return cnt;
    };
    int left = 0, right = (price.back() - price[0]) / (k - 1) + 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (checkDistance(mid) >= k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left - 1;
}

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
    std::vector<int> piles = {312884470};
    std::cout << "875. Koko Eating Bananas : piles = [312884470], h = 968709470 : " << minEatingSpeed(piles, 968709470) << std::endl;

    std::vector<int> times = {1,2,3};
    std::cout << "2187. Minimum Time to Complete Trips : time = [1,2,3], totalTrips = 5 : " << minimumTime(times, 5) << std::endl;


    std::vector<int> nums = {3,7,1,6};
    std::cout << "2439. Minimize Maximum of Array : nums = [3,7,1,6] : " << minimizeArrayValue(nums) << std::endl;

    std::vector<int> nums1 = {13,13,20,0,8,9,9};
    std::cout << "2439. Minimize Maximum of Array : nums = [13,13,20,0,8,9,9] : " << minimizeArrayValue(nums1) << std::endl;


    return 0;
}