#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>
#include<array>

/* 56. Merge Intervals */
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    size_t size = intervals.size();
    if (size == 1) {
        return intervals;
    }
    std::vector<std::vector<int>> results;
    std::sort(intervals.begin(), intervals.end());
    int left = intervals[0][0], right = intervals[0][1];
    for (int i = 0; i < size; i++) {
        if ((right >= intervals[i][0] && left <= intervals[i][1]) || (left >= intervals[i][0] && left <= intervals[i][1])) {
            left = std::min(left, intervals[i][0]);
            right = std::max(right, intervals[i][1]);
            continue;
        }
        results.push_back({left, right});
        left = intervals[i][0];
        right = intervals[i][1];
    }
    results.push_back({left, right});
    return results;
}

int main()
{
    std::cout << "Testing for Problem 56. Merge Intervals : " << std::endl;
    // std::vector<std::vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    // auto res1 = merge(intervals1);
    // for (auto &vec : res1) {
    //     std::cout << vec[0] << ", " << vec[1] << " " << std::endl;
    // }
    std::vector<std::vector<int>> intervals1 = {{1,4},{0, 0}};
    auto res1 = merge(intervals1);
    for (auto &vec : res1) {
        std::cout << vec[0] << ", " << vec[1] << " " << std::endl;
    }

    return 0;
}