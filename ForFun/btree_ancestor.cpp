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
    std::string result;
    std::function<TreeNode*(TreeNode*, int, int)> postDFS = [&](TreeNode *node, int p1, int q1) {
        if (node == nullptr || node->val == p1 || node->val == q1) {
            return node;
        }
        auto left = postDFS(node->left, p1, q1);
        auto right = postDFS(node->right, p1, q1);
        if (left && right) {
            return node;
        } else if (left) {
            return left;
        } else {
            return right;
        }
    };
    auto lcaNode = postDFS(root, startValue, destValue);
    std::function<bool(TreeNode*, int)> findStartVal = [&](TreeNode *node, int p1) -> bool {
        if (node == nullptr) {
            return false;
        }
        if (node->val == p1) {
            return true;
        }
        auto left = findStartVal(node->left, p1);
        if (left) {
            result += "U";
            return left;
        }
        auto right = findStartVal(node->right, p1);
        if (right) {
            result += "U";
            return right;
        }
        return false;
    };
    findStartVal(lcaNode, startValue);
    std::string destStr;
    std::function<bool(TreeNode*, int)> findEndVal = [&](TreeNode *node, int p1) -> bool {
        if (node == nullptr) {
            return false;
        }
        if (node->val == p1) {
            return true;
        }
        auto left = findEndVal(node->left, p1);
        if (left) {
            destStr += "L";
            return left;
        }
        auto right = findEndVal(node->right, p1);
        if (right) {
            destStr += "R";
            return right;
        }
        return false;
    };
    findEndVal(lcaNode, destValue);
    std::reverse(destStr.begin(), destStr.end());
    result += destStr;
    return result;
}