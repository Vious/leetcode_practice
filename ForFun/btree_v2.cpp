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


using namespace std;

/* 
1. Recursion
2. Mathematical induction
3. Stack
 */
/* Definition for singly-linked list. */ 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 100. Same Tree */
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) {
        return true;
    }
    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

/* 101. Symmetric Tree */
bool isSymmetric(TreeNode* root) {
    std::function<bool(TreeNode*, TreeNode*)> checkSame;
    checkSame = [&](TreeNode *p, TreeNode *q) -> bool {
        if (p == nullptr || q == nullptr) {
            return p == q;
        }
        return p->val == q->val && checkSame(p->left, q->right) && checkSame(p->right, q->left);
    };
    return checkSame(root->left, root->right);
}

/* 110. Balanced Binary Tree */
bool isBalanced(TreeNode* root) {
    std::function<int(TreeNode*)> checkBalanceDFS;
    checkBalanceDFS = [&](TreeNode *node) -> int {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = checkBalanceDFS(node->left);
        if (leftDepth == -1) {
            return -1;
        }
        int rightDepth = checkBalanceDFS(node->right);
        if (rightDepth == -1 || std::abs(rightDepth - leftDepth) > 1) {
            return -1;
        } 
        return std::max(leftDepth, rightDepth) + 1;
    };
    return checkBalanceDFS(root) != -1;
}

/* 199. Binary Tree Right Side View */
/* a very good dfs solution I learned */
vector<int> rightSideView(TreeNode* root) {
    std::vector<int> results;
    std::function<void(TreeNode*, int)> depthDFS;
    depthDFS = [&](TreeNode *node, int depth) {
        if (node == nullptr) {
            return;
        }
        /* would be same as depth >= results.size() */
        if (depth == results.size()) {
            results.push_back(node->val);
        }
        depthDFS(node->right, depth + 1);
        depthDFS(node->left, depth + 1);
    };
    depthDFS(root, 0);
    return results;
}

/* 965. Univalued Binary Tree */
bool isUnivalTree(TreeNode* root) {
    int uniValue = root->val;
    std::function<bool(TreeNode*)> uniDFS;
    uniDFS = [&](TreeNode *node) -> bool {
        if (node == nullptr) {
            return true;
        }
        if (node->val != uniValue) {
            return false;
        }
        return uniDFS(node->left) && uniDFS(node->right);
    };
    return uniDFS(root);
}

/*  */