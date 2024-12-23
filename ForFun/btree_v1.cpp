#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <ranges>
#include <queue>
#include <numeric>
#include <list>
#include <stack>


/* 
1. Recursion
2. Mathematical induction
3. Stack
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

/* 104. Maximum Depth of Binary Tree */
int maxDepth(TreeNode* root) {
    /* v1: simple recursive */
    // if (root == nullptr) {
    //     return 0;
    // }
    // int leftMax = maxDepth(root->left);
    // int rightMax = maxDepth(root->right);
    // return std::max(leftMax, rightMax) + 1;

    int result = 0;
    std::function<void(TreeNode*, int)> countDepth;
    countDepth = [&](TreeNode *node, int count) -> void {
        if (node == nullptr) {
            return;
        }
        count++;
        result = std::max(result, count);
        countDepth(node->left, count);
        countDepth(node->right, count);
    };
    countDepth(root, 0);
    return result;
}

/* 111. Minimum Depth of Binary Tree */
int minDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int result = INT32_MAX;
    std::function<void(TreeNode*, int)> dfs;
    dfs = [&](TreeNode *node, int count) {
        if(node == nullptr) {
            return;
        }
        count++;
        if (node->left == nullptr && node->right == nullptr) {
            result = std::min(result, count);
            return;
        }
        dfs(node->left, count);
        dfs(node->right, count);
    };
    dfs(root, 0);
    return result;
}

/* 112. Path Sum */
bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) {
        return false;
    }
    bool result = false;
    std::function<void(TreeNode*, int, int)> dfsSum;
    dfsSum = [&](TreeNode* node, int target, int tmpSum) -> void {
        if (node == nullptr) {
            return;
        }
        tmpSum += node->val;
        if (!result && node->left == nullptr && node->right == nullptr) {
            result = (target == tmpSum);
            return;
        }
        if (!result) {
            dfsSum(node->left, target, tmpSum);
            dfsSum(node->right, target, tmpSum);
        }
    };
    dfsSum(root, targetSum, 0);
    return result;
}

/* 129. Sum Root to Leaf Numbers */
int sumNumbers(TreeNode* root) {
    long long result = 0;
    std::function<void(TreeNode*, int )> dfsSumNum;
    dfsSumNum = [&](TreeNode *node, int curValue) {
        if (node == nullptr) {            
            return;
        }
        curValue = curValue * 10 + node->val;
        if (node->left == nullptr && node->right == nullptr) {
            result += curValue;
            return;
        }
        dfsSumNum(node->left, curValue);
        dfsSumNum(node->right, curValue);
    };
    dfsSumNum(root, 0);
    return result;
}

/* 1448. Count Good Nodes in Binary Tree */
int goodNodes(TreeNode* root) {
    int result = 0;
    std::function<void(TreeNode*, int)> cntGood;
    cntGood = [&](TreeNode *node, int value) {
        if (node == nullptr) {
            return;
        }
        if (node->val >= value) {
            result++;
        }
        int newValue = std::max(node->val, value);
        cntGood(node->left, newValue);
        cntGood(node->right, newValue);
    };
    cntGood(root, INT32_MIN);
    return result;
}

/* 987. Vertical Order Traversal of a Binary Tree */
vector<vector<int>> verticalTraversal(TreeNode* root) {
    std::vector<std::vector<int>> results;
    std::map<int, vector<std::pair<int, int>>> matrixMap;
    std::function<void(TreeNode*, int, int)> verTrav;
    verTrav = [&](TreeNode *node, int row, int column) {
        if (node == nullptr) {
            return;
        }
        matrixMap[column].emplace_back(std::make_pair(row, node->val));
        verTrav(node->left, row + 1, column - 1);
        verTrav(node->right, row + 1, column + 1);
    };
    verTrav(root, 0, 0);
    for(auto &[_, group] : matrixMap) {
        ranges::sort(group);
        std::vector<int> tmpVec;
        for (auto aPair : group) {
            tmpVec.push_back(aPair.second);
        }
        results.emplace_back(tmpVec);
    }
    return results;
}

/* 2471. Minimum Number of Operations to Sort a Binary Tree by Level */
/* BFS */
int minimumOperations(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    }
    /* adopt priority queue to make it faster, below solution code is too brute-force */
    int result = 0;
    std::vector<TreeNode*> nodelist;
    if (root->left != nullptr) {
        nodelist.emplace_back(root->left);
    }
    if (root->right != nullptr) {
        nodelist.emplace_back(root->right);
    }
    while(!nodelist.empty()) {
        std::vector<int> tmpVec;
        std::vector<TreeNode*> newNodeList;
        for (auto node : nodelist) {
            tmpVec.push_back(node->val);
            if (node->left) {
                newNodeList.emplace_back(node->left);
            }
            if (node->right) {
                newNodeList.emplace_back(node->right);
            }
        }
        nodelist = std::move(newNodeList);
        int size = tmpVec.size();
        for (int i = 0; i < size; i++) {
            int mindex = std::distance(tmpVec.begin(), ranges::min_element(tmpVec.begin() + i, tmpVec.end()));
            if (mindex == i) {
                continue;
            } else {
                std::swap(tmpVec[mindex], tmpVec[i]);
                result++;
            }
        }
    }
    return result;
}

int main() {
    TreeNode *node = new TreeNode();
    std::cout << "Max node : " << maxDepth(node) << std::endl;
}