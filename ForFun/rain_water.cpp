#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/* 11. Container With Most Water */
int maxArea(std::vector<int>& height) {
    int size = height.size();
    int left = 0, right = size - 1;
    int res = 0;
    while(left < right) {
        if (height[left] <= 0) {
            left++;
        } else if (height[right] <= 0) {
            right--;
        } else {
            int volume = std::min(height[right], height[left]) * (right - left);
            res = std::max(volume, res);
            if (height[right] > height[left]) {
                left++;
            } else {
                right--;
            }
        }
    }
    return res;
}

/* 42. Trapping Rain Water */
int trap(std::vector<int>& height) {
    /* solution 1 : prefix & suffix max */
    // int size = height.size();
    // std::vector<int> prefMax(size, 0);
    // prefMax[0] = height[0];
    // for (int i = 1; i < size; i++) {
    //     prefMax[i] = std::max(height[i], prefMax[i - 1]);
    // }

    // std::vector<int> sufMax(size, 0);
    // sufMax[size - 1] = height[size - 1];
    // for (int i = size - 2; i >= 0; i--) {
    //     sufMax[i] = std::max(height[i], sufMax[i + 1]);
    // }
    
    // int result = 0;
    // for (int i = 0; i < size; i++) {
    //     result += (std::min(sufMax[i], prefMax[i]) - height[i]);
    // }
    // return result;
    /* second solution: save space */
    int size = height.size();
    int left = 0, right = size - 1;
    int result = 0, prefMax = 0, sufMax = 0;
    while(left <= right) {
        prefMax = std::max(prefMax, height[left]);
        sufMax = std::max(sufMax, height[right]);
        if (prefMax <= sufMax) {
            result += (prefMax - height[left]);
            left++;
        } else {
            result += (sufMax - height[right]);
            right--;
        }
    }
    return result;
}

int main()
{
    std::vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "42. Trapping Rain Water nums = {0,1,0,2,1,0,1,3,2,1,2,1} : " << trap(nums) << std::endl;
    return 0;
}