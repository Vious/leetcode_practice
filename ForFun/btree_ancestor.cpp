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
topic here is Most common ancestor
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

/* 236. Lowest Common Ancestor of a Binary Tree */
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) {
        return root;
    }
    auto left = lowestCommonAncestor(root->left, p, q);
    auto right = lowestCommonAncestor(root->right, p, q);

    if (left && right) {
        return root;
    } else if (left) {
        return left;
    } else {
        return right;
    }
}

/* 235. Lowest Common Ancestor of a Binary Search Tree */
TreeNode* lowestCommonAncestorV2(TreeNode* root, TreeNode* p, TreeNode* q) {
    int curVal = root->val;
    if (p->val < curVal && q->val < curVal) {
        return lowestCommonAncestorV2(root->left, p, q);
    } else if (p->val > curVal && q->val > curVal) {
        return lowestCommonAncestorV2(root->right, p, q);
    } else {
        return root;
    }
}

/* 1123. Lowest Common Ancestor of Deepest Leaves */
TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /* following is a wrong understanding of this problem */
    // if (root == nullptr) {
    //     return nullptr;
    // }
    // if (!root->left && !root->right) {
    //     return root;
    // }
    // std::vector<TreeNode*> nodes;
    // nodes.emplace_back(root);
    // std::queue<std::vector<TreeNode*>> twoLayers;
    // twoLayers.push(nodes);
    // std::vector<TreeNode*> tmpNodes;
    // while(!nodes.empty()) {
    //     tmpNodes.clear();
    //     for (auto aNode : nodes) {
    //         if (aNode->left) {
    //             tmpNodes.emplace_back(aNode->left);
    //         }
    //         if (aNode->right) {
    //             tmpNodes.emplace_back(aNode->right);
    //         }
    //     }
    //     nodes = std::move(tmpNodes);
    //     if (!nodes.empty()) {
    //         if (twoLayers.size() == 2) {
    //             twoLayers.pop();
    //             twoLayers.push(nodes);
    //         } else {
    //             twoLayers.push(nodes);
    //         }
    //     }
    // }
    // auto ancestors = twoLayers.front();
    // twoLayers.pop();
    // auto leaves = twoLayers.front();
    // for (auto res : ancestors) {
    //     for (auto aLeaf : leaves) {
    //         if (res->left == aLeaf || res->right == aLeaf) {
    //             return res;
    //         }
    //     }
    // }
    // return ancestors[0];
    TreeNode *result;
    int maxDepth = -1;
    std::function<int(TreeNode*, int)> postOrderDFS = [&](TreeNode *node, int depth) {
        if (node == nullptr) {
            maxDepth = std::max(maxDepth, depth);
            return depth;
        }
        int leftDepth = postOrderDFS(node->left, depth + 1);
        int rightDepth = postOrderDFS(node->right, depth + 1);
        if (leftDepth == rightDepth && rightDepth == maxDepth) {
            result = node;
        }
        return std::max(leftDepth, rightDepth);
    };
    postOrderDFS(root, 0);
    return result;
}

/* 2096. Step-By-Step Directions From a Binary Tree Node to Another */
string getDirections(TreeNode* root, int startValue, int destValue) {
    
}