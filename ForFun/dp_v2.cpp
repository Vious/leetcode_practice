#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>
#include <set>
#include <stack>
#include <functional>

/* 
dynamic programming v2: 
Knapsack problem
*/
using namespace std;

/* 494. Target Sum */
int findTargetSumWays(vector<int>& nums, int target) {
    /* consider all postive sum is:
        p
        all sum: s
        negative ones : s - p
        p - (s - p) = t
        p = (s + t) / 2
    */
/*  
    Time Limit Exceeded
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    target += sum;
    if (target < 0 || (target % 2 != 0)) {
        return 0;
    }
    target /= 2;
    std::function<int(int, int)> dfs = [&](int i, int tmpTarget) {
        if (i < 0) {
            return tmpTarget == 0 ? 1 : 0;
        } 
        if (tmpTarget < nums[i]) {
            dfs(i - 1, tmpTarget);
        }
        return dfs(i - 1, tmpTarget - nums[i]) + dfs(i - 1, tmpTarget);
    };
    int size = nums.size() - 1;
    return dfs(size, target);
 */

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    target += sum;
    if (target < 0 || (target % 2 != 0)) {
        return 0;
    }
    target /= 2;
    int size = nums.size();
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(target + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= target; j++) {
            if (j < nums[i]) {
                dp[i + 1][j] = dp[i][j];
            } else {
                dp[i + 1][j] = dp[i][j] + dp[i][j - nums[i]];
            }
        }
    }
    return dp[size][target];
}

/* remained:
2915. 和为目标值的最长子序列的长度 https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/
416. 分割等和子集 https://leetcode.cn/problems/partition-equal-subset-sum/
2787. 将一个数字表示成幂的和的方案数 https://leetcode.cn/problems/ways-to-express-an-integer-as-sum-of-powers/
518. 零钱兑换 II https://leetcode.cn/problems/coin-change-ii/
279. 完全平方数 https://leetcode.cn/problems/perfect-squares/
 */

int main()
{
    std::vector<int> nums = {1};
    std::cout << "Testing 494. Target Sum: nums = [1,1,1,1,1], target = 3, result:" << findTargetSumWays(nums, 1) << std::endl;
    return 0;
}