#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cstring>

/* 46. Permutations */
void backtracePermute(std::vector<std::vector<int>> &results, std::vector<int>& nums, std::vector<int> tmpResults, bool visited[]) {
    if (tmpResults.size() == nums.size()) {
        results.emplace_back(tmpResults);
        return;
    }
    size_t size = nums.size();
    for (int i = 0; i < size; i++) {
        if (visited[i]) {
            continue;
        } else {
            tmpResults.push_back(nums[i]);
            visited[i] = true;
            backtracePermute(results, nums, tmpResults, visited);
            tmpResults.pop_back();
            visited[i] = false;
        }
    }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    size_t size = nums.size();
    std::vector<std::vector<int>> results;
    if (size <= 1) {
        results.emplace_back(nums);
        return results;
    }
    bool visited[size];
    std::memset(visited, false, sizeof(visited));
    std::vector<int> tmpResults;
    backtracePermute(results, nums, tmpResults, visited);

    return results;
}
/* more efficient code below */
void permuteHelper(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
    if (start == nums.size()) {
        result.push_back(nums);
        return;
    }
    
    for (int i = start; i < nums.size(); ++i) {
        std::swap(nums[start], nums[i]);           // Swap the current element with the start element
        permuteHelper(nums, start + 1, result); // Recur for the next element
        std::swap(nums[start], nums[i]);           // Backtrack to restore the original array
    }
}

/* 47. Permutations II */
void backtraceUniquePermute(std::vector<std::vector<int>> &results, std::vector<int>& nums, std::vector<int> tmpResults, bool visited[]) {
    if (tmpResults.size() == nums.size()) {
        results.emplace_back(tmpResults);
        return;
    }
    size_t size = nums.size();
    for (int i = 0; i < size; i++) {
        if (visited[i]) {
            continue;
        } else {
            if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) {
                continue;
            }
            tmpResults.push_back(nums[i]);
            visited[i] = true;
            backtraceUniquePermute(results, nums, tmpResults, visited);
            tmpResults.pop_back();
            visited[i] = false;
        }
    }
}

std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
    size_t size = nums.size();
    std::vector<std::vector<int>> results;
    if (size <= 1) {
        results.emplace_back(nums);
        return results;
    }
    bool visited[size];
    std::sort(nums.begin(), nums.end());
    std::memset(visited, false, sizeof(visited));
    std::vector<int> tmpResults;
    backtraceUniquePermute(results, nums, tmpResults, visited);

    return results;
}

/* 48. Rotate Image */
void rotate(std::vector<std::vector<int>>& matrix) {
    int N = matrix.size();
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[N - j - 1][i];
            matrix[N - j - 1][i] = matrix[N - i - 1][N - j - 1];
            matrix[N - i - 1][N - j - 1] = matrix[j][N - i - 1];
            matrix[j][N - i - 1] = tmp;
        }
    }
}

/* 49. Group Anagrams */
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    // std::vector<std::vector<std::string>> results;
    // if (strs.empty()) {
    //     return results;
    // }
    // int size = strs.size();
    // if (size == 1) {
    //     results.emplace_back(strs);
    //     return results;
    // }
    // bool visited[size + 1];
    // std::memset(visited, false, sizeof(visited));
    // for (int i = 0; i < size; i++) {
    //     if (visited[i]) {
    //         continue;
    //     }
    //     std::vector<std::string> tmpStrs;
    //     tmpStrs.emplace_back(strs[i]);
    //     visited[i] = true;
    //     for (int j = i + 1; j < size; j++) {
    //         if (visited[j]) {
    //             continue;
    //         } else {
    //             std::string aStr = strs[j];
    //             std::string inGroup = tmpStrs[0];
    //             std::sort(aStr.begin(), aStr.end());
    //             std::sort(inGroup.begin(), inGroup.end());
    //             if (aStr == inGroup) {
    //                 visited[j] = true;
    //                 tmpStrs.emplace_back(strs[j]);
    //             }
    //         }
    //     }
    //     results.emplace_back(tmpStrs);

    // }
    // return results;
    /* The above code meets Time Limit Exceeded problem on leetcode server */
    // I adopt hashmap below
    std::vector<std::vector<std::string>> results;
    if (strs.empty()) {
        return results;
    }
    int size = strs.size();
    if (size == 1) {
        results.emplace_back(strs);
        return results;
    }
    std::unordered_map<std::string, std::vector<std::string>> hashMap;
    for (int i = 0; i < size; i++) {
        std::string aStr = strs[i];
        std::sort(aStr.begin(), aStr.end());
        hashMap[aStr].emplace_back(strs[i]);
    }
    for(auto iter = hashMap.begin(); iter != hashMap.end(); iter++) {
        results.emplace_back(iter->second);
    }

    return results;
}

/* 50. Pow(x, n) */
double myPow(double x, int n) {
    if (x == 0.0) {
        return 0.0;
    } else if (n == 0) {
        return 1.0;
    } else if (n == 1) {
        return x;
    }
    // preventing for INT_MIN
    long long int longN = n;
    if (n < 0) {
        x = 1 / x;
        longN = -longN;
    }
    double result = 1.0;
    while(longN) {
        if (longN % 2 == 1) {
            result *= x;
        }
        x *= x;
        longN /= 2;
    } 
    return result;

}

int main()
{
    std::cout << "Testing for Problem 46. Permutations : " << std::endl;
    std::cout << "Test for nums = [1,2,3]: " << std::endl;
    std::vector<int> nums = {1,2,3};
    auto res = permute(nums);
    for (auto &vec : res) {
        for (auto &ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Testing for Problem 47. Permutations II : " << std::endl;
    std::cout << "Test for nums = [1,1,2]: " << std::endl;
    std::vector<int> nums2 = {1,1,2};
    auto res2 = permuteUnique(nums2);
    for (auto &vec : res2) {
        for (auto &ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Testing for Problem 48. Rotate Image : " << std::endl;
    std::cout << "Test for nums = [[1,2,3],[4,5,6],[7,8,9]]: " << std::endl;
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    rotate(matrix);
    for (auto &vec : matrix) {
        for (auto &ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Testing for Problem 49. Group Anagrams : " << std::endl;
    std::vector<std::string> strs = {"eat","tea","tan","ate","nat","bat"};
    auto res3 = groupAnagrams(strs);
    for (auto &vec : res3) {
        for (auto &ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Testing for Problem 50. Pow(x, n) : " << std::endl;
    std::cout << "Test for x = 2.00000, n = 10: " << myPow(2.00000, 10) << std::endl;
    std::cout << "Test for x = 2.10000, n = 3: " << myPow(2.10000, 3) << std::endl;
    std::cout << "Test for x = 2.00000, n = -2: " << myPow(2.00000, -2) << std::endl;

    return 0;
}