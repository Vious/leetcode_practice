#include <iostream>
#include <vector>
#include <cmath>

/* Problem 11. (Container With Most Water) */
int maxArea(std::vector<int>& height) {
    int size = height.size();
    if (size <= 1) {
        return 0;
    }
    int left = 0, right = size - 1;
    int maxResult = (right - left) * std::min(height[left], height[right]);
    int tmpResult;
    while(left < right) {
        if(height[right] >= height[left]) {
            left++;
        } else {
            right--;
        }
        tmpResult = (right - left) * std::min(height[left], height[right]);
        maxResult = tmpResult > maxResult? tmpResult : maxResult;
    }

    return maxResult;
}

int main()
{
    std::cout << "Testing for Problem 11. (Container With Most Water): " << std::endl;
    std::vector<int> heights1 = {1,8,6,2,5,4,8,3,7};
    std::cout << "heights1 = {1,8,6,2,5,4,8,3,7}," << " maxArea: " << maxArea(heights1) << std::endl;
    std::vector<int> heights2 = {1,1};
    std::cout << "heights2 = {1,1}," << " maxArea: " << maxArea(heights2) << std::endl;

    return 0;
}