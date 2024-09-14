#include <iostream>
#include <vector>

/* 209. Minimum Size Subarray Sum */
int minSubArrayLen(int target, std::vector<int>& nums) {
    int size = nums.size();
    int ans = size + 1, sum = 0;
    int left = 0, right = left;
    while(right < size) {
        sum += nums[right];
        if (sum < target) {
            right++;
            continue;
        } else {
            // ans = std::min(ans, right - left + 1);
            while(sum >= target) {
                ans = std::min(ans, right - left + 1);
                sum -= nums[left];
                left++;
            }
            right++;
        }
    }
    return (ans == size + 1) ? 0 : ans;
}

/* 2904. Shortest and Lexicographically Smallest Beautiful String */


int main()
{
    std::cout << "Test 209. Minimum Size Subarray Sum " << std::endl;
    std::vector<int> nums = {2,3,1,2,4,3};
    std::cout << "Ans for 2,3,1,2,4,3 : " << minSubArrayLen(7, nums) << std::endl;

    return 0;
}