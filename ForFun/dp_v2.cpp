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
#include <limits>
#include <cstdint>


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
    /* solution 1: dp */
/*     int sum = std::accumulate(nums.begin(), nums.end(), 0);
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
 */
    /* solution 2: */
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    target += sum;
    if (target < 0 || (target % 2 != 0)) {
        return 0;
    }
    target /= 2;
    int size = nums.size();
    std::vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int value : nums) {
        for (int j = target; j >= value; j--) {
            dp[j] += dp[j - value];
        }
    }
    return dp[target];
}

/* 322. Coin Change */
int coinChange(vector<int>& coins, int amount) {
    /* solution 1 : recursion */
/*     int coinNum = coins.size();
    std::vector<std::vector<int>> dp(coinNum + 1, std::vector<int>(amount + 1, -1));
    std::function<int(int, int)> dfs = [&](int i, int tmpAmount) {
        if (i < 0) {
            return tmpAmount == 0 ? 0 : INT32_MAX / 2;
        }
        if (tmpAmount < coins[i]) {
            return dfs(i - 1, tmpAmount);
        }
        if (dp[i][tmpAmount] != -1) {
            return dp[i][tmpAmount];
        }
        return dp[i][tmpAmount] = std::min(dfs(i - 1, tmpAmount), dfs(i, tmpAmount - coins[i]) + 1);
    };
    int result = dfs(coinNum - 1, amount);
    return result == INT32_MAX / 2 ? -1 : result; */
    /* solution 2 : dp */
/*     int coinNum = coins.size();
    std::vector<std::vector<int>> dp(coinNum + 1, std::vector<int>(amount + 1, INT32_MAX / 2));
    dp[0][0] = 0;
    for (int i = 0; i < coinNum; i++) {
        for (int j = 0; j <= amount; j++) {
            if (j < coins[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = std::min(dp[i][j], dp[i+1][j - coins[i]] + 1);
            }
        }
    }
    return dp[coinNum][amount] == INT32_MAX / 2 ? -1 : dp[coinNum][amount];
 */
    /* solution 3: dp one array */
    int coinNum = coins.size();
    std::vector<int> dp(amount + 1, INT32_MAX / 2);
    dp[0] = 0;
    for (int val: coins) {
        for (int j = val; j <= amount; j++) {
            dp[j] = std::min(dp[j], dp[j - val] + 1);
        }
    }
    return dp[amount] == INT32_MAX / 2 ? -1 : dp[amount];
}

/* 2915. Length of the Longest Subsequence That Sums to Target */
int lengthOfLongestSubsequence(vector<int>& nums, int target) {
    int size = nums.size();
    std::vector<std::vector<int>> memo(size + 1, std::vector<int>(target + 1, -1));
    std::function<int(int, int)> dfs = [&](int i, int tmpTarget) {
        if (i < 0) {
            return tmpTarget == 0 ? 0 : INT32_MIN;
        }
        if (memo[i][tmpTarget] != -1) {
            return memo[i][tmpTarget];
        }
        if (tmpTarget < nums[i]) {
            return memo[i][tmpTarget] = dfs(i - 1, tmpTarget);
        }
        return memo[i][tmpTarget] = std::max(dfs(i - 1, tmpTarget), dfs(i - 1, tmpTarget - nums[i]) + 1);
    };
    int result = dfs(size - 1, target);
    return result > 0 ? result : -1;
}

/* 416. Partition Equal Subset Sum */
bool canPartition(vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) {
        return false;
    }
    sum /= 2;
    int size = nums.size();
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(sum + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= sum; j++) {
            if (j < nums[i]) {
                dp[i + 1][j] = dp[i][j];
            } else {
                dp[i + 1][j] = dp[i][j] || dp[i][j - nums[i]];
            }
        }
    }
    return dp[size - 1][sum] == 1;
}

/*  */

/*  */
/* remained:
2787. 将一个数字表示成幂的和的方案数 https://leetcode.cn/problems/ways-to-express-an-integer-as-sum-of-powers/
518. 零钱兑换 II https://leetcode.cn/problems/coin-change-ii/
279. 完全平方数 https://leetcode.cn/problems/perfect-squares/
 */

int main()
{
    std::vector<int> nums = {1,2,3,4,5};
    // std::cout << "Testing 494. Target Sum: nums = [1,1,1,1,1], target = 3, result:" << findTargetSumWays(nums, 1) << std::endl;

    // std::cout << "Testing 322. Coin Change: coins = [1,2,5], amount = 11, result:" << coinChange(nums, 11) << std::endl;

    std::cout << "Testing 2915. Length of the Longest Subsequence That Sums to Target: nums = [1,2,3,4,5], target = 9, result:" << lengthOfLongestSubsequence(nums, 9) << std::endl;
    return 0;
}