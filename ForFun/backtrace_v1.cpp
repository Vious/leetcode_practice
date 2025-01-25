#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>


/* 
v1 : Subset type backtracking 
*/
using namespace std;

/* Definition for singly-linked list. */ 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/* 17. Letter Combinations of a Phone Number */
vector<string> letterCombinations(string digits) {
    const std::vector<std::string> digitMap = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::vector<std::string> results;
    int size = digits.size();
    if (size == 0) {
        return results;
    }
    std::string path(size, 0);
    std::function<void(int)> dfs = [&](int num) {
        if (num == size) {
            results.emplace_back(path);
            return;
        }
        for (char ch : digitMap[digits[num] - '0']) {
            path[num] = ch;
            dfs(num + 1);
        }
    };
    dfs(0);
    return results;
}

/* 78. Subsets */
vector<vector<int>> subsets(vector<int>& nums) {
    /* solution 1* */
    // int size = nums.size();
    // std::vector<std::vector<int>> results;
    // if (size == 0) {
    //     return results;
    // }
    // std::vector<int> pathVec;
    // std::function<void(int)> dfsAdd = [&](int depth) {
    //     if (depth == size) {
    //         results.push_back(pathVec);
    //         return;
    //     }
    //     dfsAdd(depth + 1);
    //     pathVec.push_back(nums[depth]);
    //     dfsAdd(depth + 1);
    //     pathVec.pop_back();
    // };
    // dfsAdd(0);
    // return results;

    /* solution 2 */
    int size = nums.size();
    std::vector<std::vector<int>> results;
    if (size == 0) {
        return results;
    }
    std::vector<int> pathVec;
    std::function<void(int)> dfsAdd = [&](int depth) {
        results.emplace_back(pathVec);
        for (int i = depth; i < size; i++) {
            pathVec.push_back(nums[i]);
            dfsAdd(i + 1);
            pathVec.pop_back();
        }
    };
    dfsAdd(0);
    return results;
}

/* 131. Palindrome Partitioning */
bool isPalindromeString(const std::string str) {
    int size = str.size();
    int left = 0, right = size - 1;
    while(left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

vector<vector<string>> partition(string s) {
    int size = s.size();
    std::vector<std::vector<std::string>> results;
    if (size == 0) {
        return results;
    }
    std::vector<std::string> pathVec;
    std::function<void(int)> strDFS = [&](int depth) {
        if (depth == size) {
            results.emplace_back(pathVec);
            return;
        }
        for (int i = depth; i < size; i++) {
            std::string substr = s.substr(depth, i - depth + 1);
            if (isPalindromeString(substr)) {
                pathVec.emplace_back(substr);
                strDFS(i + 1);
                pathVec.pop_back();
            }
        }
    };

    strDFS(0);
    return results;
}

/* 257. Binary Tree Paths */
vector<string> binaryTreePaths(TreeNode* root) {
    std::vector<std::string> results;
    // std::string path;
    std::function<void(TreeNode*, std::string)> treeDFS = [&](TreeNode *node, std::string path) {
        if (!node->left && !node->right) {
            if (path.empty()) {
                path += std::to_string(node->val);
            } else {
                path += "->" + (std::to_string(node->val));
            }
            results.emplace_back(path);
            return;
        }
        if (path.empty()) {
            path += std::to_string(node->val);
        } else {
            path += "->" + (std::to_string(node->val));
        }
        if (node->left) {
            treeDFS(node->left, path);
        }
        if (node->right) {
            treeDFS(node->right, path);
        }        
    };
    treeDFS(root, "");
    return results;
}

/* 113. Path Sum II */
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    std::vector<std::vector<int>> results;
    std::vector<int> pathVec;
    std::function<void(TreeNode*, int)> dfs = [&](TreeNode *node, int sum) {
        if (node == nullptr) {
            return;
        }
        if (node->left == node->right) {
            sum += node->val;
            if (sum == targetSum) {
                pathVec.push_back(node->val);
                results.emplace_back(pathVec);
                pathVec.pop_back();
            }
            return;
        }
        pathVec.push_back(node->val);
        sum += node->val;
        dfs(node->left, sum);
        dfs(node->right, sum);
        pathVec.pop_back();
        sum -= node->val;
    };
    dfs(root, 0);
    return results;
}

/* 784. Letter Case Permutation */
vector<string> letterCasePermutation(string s) {
    
}

/* remaining:
784. 字母大小写全排列 https://leetcode.cn/problems/letter-case-permutation/
LCP 51. 烹饪料理 https://leetcode.cn/problems/UEcfPD/
2397. 被列覆盖的最多行数 https://leetcode.cn/problems/maximum-rows-covered-by-columns/
1239. 串联字符串的最大长度 https://leetcode.cn/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
2212. 射箭比赛中的最大得分 https://leetcode.cn/problems/maximum-points-in-an-archery-competition/
2698. 求一个整数的惩罚数 https://leetcode.cn/problems/find-the-punishment-number-of-an-integer/
306. 累加数 https://leetcode.cn/problems/additive-number/
93. 复原 IP 地址 https://leetcode.cn/problems/restore-ip-addresses/
 */

int main()
{
    std::cout << "Test 17. Letter Combinations of a Phone Number : digits = 23" << std::endl;
    auto res = letterCombinations("23");
    for (auto str : res) {
        std::cout << str << ", ";
    }
    std::cout << std::endl;

    std::cout << "Test 131. Palindrome Partitioning s = aab" << std::endl;
    std::string str = "aab";
    auto res1 = partition(str);
    for (auto vec : res1) {
        for (auto s : vec) {
            std::cout << s << ", ";
        }
        std::cout << "\n";
    }

    return 0;
}