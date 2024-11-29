#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



std::vector<int> twoSum(std::vector<int>& numbers, int target) {
    int size = numbers.size();
    int left = 0, right = size - 1;
    while(left < right) {
        int tmp = numbers[left] + numbers[right];
        if (tmp == target) {
            return {left + 1, right + 1};
        } else if (tmp > target) {
            right--;
        } else if (tmp < target) {
            left++;
        }
    }
    return {left + 1, right + 1};
}

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> results;
    int size = nums.size();
    for (int i = 0; i < size - 2; i++) {
        if (nums[i] + nums[i + 1] + nums[i + 2] > 0) {
            break;
        } else if (nums[size - 1] + nums[size - 2] + nums[size - 3] < 0) {
            break;
        }
        int val = nums[i];
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        } 
        int left = i + 1;
        int right = size - 1;
        while(left < right) {
            int tmpSum = val + nums[left] + nums[right];
            if (tmpSum > 0) {
                right--;
            } else if (tmpSum < 0) {
                left++;
            } else {
                results.push_back({nums[i], nums[left], nums[right]});
                right--;
                while(right > left && nums[right] == nums[right + 1]) {
                    right--;
                }
                left++;
                while(left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
            }
        }
    }
    return results;
}

int countPairs(std::vector<int>& nums, int target) {
    std::sort(nums.begin(), nums.end());
    int result = 0;
    int size = nums.size();
    for (int i = 0; i < size - 1; i++) {
        if (nums[i] + nums[i + 1] >= target) {
            break;
        }
        for (int j = i + 1; j < size; j++) {
            if (nums[i] + nums[j] < target) {
                result++;
            } else {
                break;
            }
        }

    }
    return result;
}

int threeSumClosest(std::vector<int>& nums, int target) {
    std::sort(nums.begin(), nums.end());
    int result = nums[0] + nums[1] + nums[2];
    int gap = INT32_MAX, size = nums.size();
    for (int i = 0; i < size - 2; i++) {
        int val = nums[i];
        int left = i + 1, right = size - 1;
        while(left < right) {
            int sum = val + nums[left] + nums[right];
            int newGap = std::abs(sum - target);
            result = newGap < gap ? sum : result;
            gap = std::min(gap, newGap);
            if (sum > target) {
                right--;
            } else if (sum < target) {
                left++;
            } else {
                return sum;
            }
        }
    }
    return result;
}

// be careful of overflow!!!!!!!!!
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    int size = nums.size();
    std::vector<std::vector<int>> results;
    if (size < 4) {
        return results;
    }
    std::sort(nums.begin(), nums.end());
    if ((long long)nums[size - 4] + nums[size - 3] + nums[size - 2] + nums[size - 1] < target) {
        return results;
    }
    for (int i = 0; i < size - 3; i++) {
        int val1 = nums[i];
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        if ((long long) nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
            break;
        }
        for (int j = i + 1; j < size - 2; j++) {
            int val2 = nums[j];
            // very essential j > i + 1 && ...
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
            int left = j + 1;
            int right = size - 1;
            while(left < right) {
                long long sum = (long long)val1 + val2 + nums[left] + nums[right];
                if (sum > target) {
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    results.push_back({val1, val2, nums[left], nums[right]});
                    left++;
                    while(left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                    right--;
                    while(right > left && nums[right] == nums[right + 1]) {
                        right--;
                    }
                }
            }
        }
    }
    return results;
}

/* 611. Valid Triangle Number  */
int triangleNumber(std::vector<int>& nums) {
    int size = nums.size();
    if (size < 3) return 0;
    int count = 0;
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < size - 2; i++) {
        if (nums[i] == 0) continue;
        int lindx = i + 2; // put it here, makes code much faster
        for (int j = i + 1; j < size - 1; j++) {
            // int lindx = j + 1;
            while(lindx < size && nums[i] + nums[j] > nums[lindx]) {
                lindx++;
            }
            count += (lindx - j) - 1;
        }
    }
    return count;
}

int main()
{
    std::vector<int> nums1 = {-2,-1,-1,1,1,2,2};
    auto res = fourSum(nums1, 0);
    for (auto vec : res) {
        for (auto ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}