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

    return 0;
}