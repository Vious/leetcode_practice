#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>
#include <set>
#include <stack>

/* 
v2 : permutation type backtracking, cutting edge
*/
using namespace std;

/* 46. Permutations */
vector<vector<int>> permute(vector<int>& nums) {
    int size = nums.size();
    std::vector<std::vector<int>> results;
    std::vector<int> path, isVisited(size, 0);
    path.reserve(size);
    std::function<void(int)> dfsPermute = [&](int depth) {
        if (depth == size) {
            results.emplace_back(path);
            return;
        }
        for (int i = 0; i < size; i++) {
            if (isVisited[i] == 0) {
                path.push_back(nums[i]);
                isVisited[i] = 1;
                dfsPermute(depth + 1);
                path.pop_back();
                isVisited[i] = 0;
            }
        }
    };
    dfsPermute(0);
    return results;
}

/* 51. N-Queens */
vector<vector<string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> results;
    std::vector<int> putQueens(n, 0);
    std::vector<int> colUsed(n, 0), diag1(2 * n - 1, 0), diag2(2 * n - 1, 0);
    std::function<void(int)> dfsSolve = [&](int row) {
        if (row == n) {
            std::vector<std::string> aBoard(n);
            for (int i = 0; i < n; i++) {
                aBoard[i] = std::string(putQueens[i], '.') + "Q" + std::string(n - putQueens[i] - 1, '.');
            }
            results.emplace_back(aBoard);
            return;
        }
        for (int col = 0; col < n; col++) {
            int rc = row - col + n - 1;
            if (!colUsed[col] && !diag1[row + col] && !diag2[rc]) {
                putQueens[row] = col;
                colUsed[col] = diag1[row + col] = diag2[rc] = 1;
                dfsSolve(row + 1);
                colUsed[col] = diag1[row + col] = diag2[rc] = 0;
            }
        }
    };
    dfsSolve(0);
    return results;
}

/* 52. N-Queens II */
int totalNQueens(int n) {
    int results = 0;
    std::vector<int> putQueens(n, 0);
    std::vector<int> colUsed(n, 0), diag1(2 * n - 1, 0), diag2(2 * n - 1, 0);
    std::function<void(int)> dfsSolve = [&](int row) {
        if (row == n) {
            results++;
            return;
        }
        for (int col = 0; col < n; col++) {
            int rc = row - col + n - 1;
            if (!colUsed[col] && !diag1[row + col] && !diag2[rc]) {
                putQueens[row] = col;
                colUsed[col] = diag1[row + col] = diag2[rc] = 1;
                dfsSolve(row + 1);
                colUsed[col] = diag1[row + col] = diag2[rc] = 0;
            }
        }
    };
    dfsSolve(0);
    return results;
}

/* 357. Count Numbers with Unique Digits */
int countNumbersWithUniqueDigits(int n) {
    
}

/* remaining:
357. 统计各位数字都不同的数字个数 https://leetcode.cn/problems/count-numbers-with-unique-digits/
2850. 将石头分散到网格图的最少移动次数 https://leetcode.cn/problems/minimum-moves-to-spread-stones-over-grid/
 */

int main()
{
    std::cout << "Test 46. Permutations, nums = [1, 2, 3]: " << std::endl;
    std::vector<int> nums = {1, 2, 3};
    auto res1 = permute(nums);
    for (auto vec : res1) {
        for (int val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}