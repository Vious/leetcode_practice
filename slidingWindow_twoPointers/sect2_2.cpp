#include <iostream>
#include <vector>
#include <string>
#include <cstring>

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
std::string shortestBeautifulSubstring(std::string s, int k) {
    int size = s.size();
    std::string ans = "";
    int ansSize = size + 1;
    int left = 0, right = left;
    int count = 0;
    while(right <= size) {
        if (count < k) {
            if (s[right] == '1') {
                count++;
            }
            right++;
        } 
        if (count == k) {
            while(s[left] == '0') {
                left++;
            }
            int curLen = right - left;
            if (curLen < ansSize) {
                ans = s.substr(left, right - left);
                ansSize = curLen;
            } else if (curLen == ansSize) {
                if (ans > s.substr(left, curLen)) {
                    ans = s.substr(left, curLen);
                }
            }
            if (s[left] == '1') {
                left++;
                count--;
            }
            // right++;
        }
    }

    return ans;
}

/*  */

int main()
{
    std::cout << "Test 209. Minimum Size Subarray Sum " << std::endl;
    std::vector<int> nums = {2,3,1,2,4,3};
    std::cout << "Ans for 2,3,1,2,4,3 : " << minSubArrayLen(7, nums) << std::endl;

    std::cout << "Test 2904. Shortest and Lexicographically Smallest Beautiful String " << std::endl;
    std::cout << "Test str 100011001 : " << shortestBeautifulSubstring("100011001", 3) << std::endl;
    std::cout << "Test str 1011 : " << shortestBeautifulSubstring("1011", 2) << std::endl;
    return 0;
}