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

/* 57. Insert Interval */
std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
    // the following code are cost O(N) time complexity
    size_t size = intervals.size();
    std::vector<std::vector<int>> results;
    if (size == 0) {
        results.emplace_back(newInterval);
        return results;
    }
    std::vector<int> tmpInterval = newInterval;
    for (int i = 0; i < size; i++) {
        if ((tmpInterval[1] >= intervals[i][0] && tmpInterval[0] <= intervals[i][1]) || (tmpInterval[0] >= intervals[i][0] && tmpInterval[0] <= intervals[i][1])) {
            tmpInterval[0] = std::min(tmpInterval[0], intervals[i][0]);
            tmpInterval[1] = std::max(tmpInterval[1], intervals[i][1]);
            continue;
        }
        if (tmpInterval[0] > intervals[i][1]) {
            results.push_back({intervals[i][0], intervals[i][1]});
        } else {
            results.push_back({tmpInterval[0], tmpInterval[1]});
            tmpInterval = intervals[i];
        }
    }
    results.emplace_back(tmpInterval);
    
    return results;
}

/* 58. Length of Last Word */
int lengthOfLastWord(std::string s) {
    size_t size = s.size();
    if (size == 1) {
        return (s[0]) != ' ' ? 1 : 0; 
    }
    int count = 0;
    int goBack = size - 1;
    bool flag = false;
    while(goBack >= 0) {
        if (s[goBack] == ' ' && !flag) {
            goBack--;
        } else {
            if(s[goBack] == ' ') {
                break;
            }
            count++;
            goBack--;
            flag = true;
        }
    }

    return count;
}

/* 59. Spiral Matrix II */
std::vector<std::vector<int>> generateMatrix(int n) {
    if (n == 1) {
        return {{1}};
    }
    std::vector<std::vector<int>> results(n, std::vector<int>(n));
    int row = 0, col = 0, dy = 1, dx = -1;
    int leftBound = 0, rightBound = n - 1, upperBound = 1, bottomBound = n - 1;
    int count = 1;
    bool turn = false;
    for (int i = 0; i < n * n ; i++) {
        results[row][col] = count;
        if (!turn) {
            col += dy;
            count++;
            if (col == rightBound + 1 || col == leftBound - 1) {
                col = (col == rightBound + 1) ? rightBound : leftBound;
                rightBound = (col == rightBound) ? --rightBound : rightBound;
                leftBound = (col == leftBound) ? ++leftBound : leftBound;
                turn = true;
                dx = -dx;
                row += dx;
            }
        } else {
            row += dx;
            count++;
            if (row == bottomBound + 1 || row == upperBound - 1) {
                row = (row == bottomBound + 1) ? bottomBound : upperBound;
                bottomBound = (row == bottomBound) ? --bottomBound : bottomBound;
                upperBound = (row == upperBound) ? ++upperBound : upperBound;
                turn = false;
                dy = -dy;
                col += dy;
            }
        }
    }
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

    std::cout << "Testing for Problem 57. Insert Interval : " << std::endl;
    std::vector<std::vector<int>> intervals2 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> newInterval = {4, 8};
    auto res2 = insert(intervals2, newInterval);
    for (auto &vec : res2) {
        std::cout << vec[0] << ", " << vec[1] << " " << std::endl;
    }

    std::cout << "Testing for Problem 58. Length of Last Word : " << std::endl;
    std::cout << "Test \"   fly me   to   the moon  \" : " << lengthOfLastWord("   fly me   to   the moon  ") << std::endl;
    std::cout << "Test \"luffy is still joyboy\" : " << lengthOfLastWord("luffy is still joyboy") << std::endl;
    std::cout << "Test \"Hello World\" : " << lengthOfLastWord("Hello World") << std::endl;


    std::cout << "Testing for Problem 59. Spiral Matrix II : " << std::endl;
    auto res3 = generateMatrix(5);
    for (auto &vec : res3) {
        for (int ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}