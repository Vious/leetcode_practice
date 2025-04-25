#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>
#include <set>
#include <stack>

/* dynamic programming v1:  */
using namespace std;

/* 740. Delete and Earn */
/* reference: 
https://leetcode.cn/problems/delete-and-earn/solutions/3061028/zhi-yu-da-jia-jie-she-pythonjavaccgojsru-e5gg/
 */
int robLike(vector<int>& nums) {
    int f0 = 0, f1 = 0;
    for (int x : nums) {
        int new_f = std::max(f1, f0 + x);
        f0 = f1;
        f1 = new_f;
    }
    return f1;
}

int deleteAndEarn(vector<int>& nums) {
    int maxNum = ranges::max(nums);
    std::vector<int> numSum(maxNum + 1, 0);
    for (int x : nums) {
        numSum[x] += x;
    }
    return robLike(numSum);
}

int main()
{

    return 0;
}