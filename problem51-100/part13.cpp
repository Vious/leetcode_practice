#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 61. Rotate List */
ListNode* rotateRight(ListNode* head, int k) {
    if (k == 0 || !head || !head->next) {
        return head;
    }
    ListNode *tmpNode = head;
    int count = 1;
    while(tmpNode->next) {
        tmpNode = tmpNode->next;
        count++;
    }
    k %= count;
    if (k == 0) {
        return head;
    }
    tmpNode->next = head;
    for (int i = 0; i < count - k; i++) {
        head = head->next;
        tmpNode = tmpNode->next;
    }
    tmpNode->next = nullptr;
    return head;
}

/* 62. Unique Paths */
int uniquePaths(int m, int n) {
    int dp[m][n];
    std::memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i < n; i++ ) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < m; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

/* 63. Unique Paths II */
int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
    size_t m = obstacleGrid.size(), n = obstacleGrid[0].size();
    int dp[m][n];
    std::memset(dp, 0, sizeof(dp));
    dp[0][0] = obstacleGrid[0][0] ? 0 : 1;
    for (int i = 1; i < n; i++ ) {
        if (obstacleGrid[0][i]) {
            break;
        }
        dp[0][i] = dp[0][i - 1];
    }
    for (int i = 1; i < m; i++) {
        if (obstacleGrid[i][0]) {
            break;
        }
        dp[i][0] = dp[i - 1][0];
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[i][j] || (obstacleGrid[i-1][j] && obstacleGrid[i][j - 1])) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
    return dp[m - 1][n - 1];
}

/* 64. Minimum Path Sum */
int minPathSum(std::vector<std::vector<int>>& grid) {
    size_t m = grid.size(), n = grid[0].size();
    int dp[m][n];
    std::memset(dp, 0, sizeof(dp));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < n; i++) {
        dp[0][i] = dp[0][i - 1] + grid[0][i];
    }
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }
    return dp[m - 1][n - 1];
}

/*  */

int main()
{
    std::cout << "Testing for Problem 61. Rotate List : " << std::endl;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5))));
    head = rotateRight(head, 2);
    for (auto ptr = head; ptr; ptr = ptr->next) {
        std::cout << ptr->val << " ";
    }
    std::cout << std::endl;

    std::cout << "Testing for Problem 62. Unique Paths : " << std::endl;
    std::cout << "Test for Input: m = 3, n = 7 : " << uniquePaths(3, 7) << std::endl;
    std::cout << "Test for Input: m = 3, n = 2 : " << uniquePaths(3, 2) << std::endl;


    std::cout << "Testing for Problem 63. Unique Paths II : " << std::endl;
    // std::vector<std::vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0 , 0}};
    // std::vector<std::vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0 , 0}};
    std::vector<std::vector<int>> grid = {{1, 0}};
    std::cout << "Test for Input: : " << uniquePathsWithObstacles(grid) << std::endl;

    std::cout << "Testing for Problem 64. Minimum Path Sum : " << std::endl;
    std::vector<std::vector<int>> grid2 = {{1,3,1},{1,5,1},{4,2,1}};
    std::cout << "Test for Input: : " << minPathSum(grid2) << std::endl;

    std::cout << "Testing for Problem 65. Valid Number : " << std::endl;

    return 0;
}