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
#include <set>

using namespace std;
/* Level Order Traversal of Binary Tree */

/* Definition for singly-linked list. */ 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 102. Binary Tree Level Order Traversal */
vector<vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> results;
    if (root == nullptr) {
        return results;
    }
    std::queue<TreeNode*> nodeQueue;
    std::vector<int> values;
    nodeQueue.push(root);
    while(!nodeQueue.empty()) {
        int size = nodeQueue.size();
        values.clear();
        for (int i = 0; i < size; i++) {
            auto aNode = nodeQueue.front();
            nodeQueue.pop();
            values.push_back(aNode->val);
            if (aNode->left) {
                nodeQueue.push(aNode->left);
            }
            if (aNode->right) {
                nodeQueue.push(aNode->right);
            }
        }
        results.emplace_back(values);
    }
    return results;
}

/* 103. Binary Tree Zigzag Level Order Traversal */
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    std::vector<std::vector<int>> results;
    if (root == nullptr) {
        return results;
    }
    std::queue<TreeNode*> nodeQueue;
    std::vector<int> values;
    nodeQueue.push(root);
    int count = 0;
    while(!nodeQueue.empty()) {
        int size = nodeQueue.size();
        values.clear();
        for (int i = 0; i < size; i++) {
            auto aNode = nodeQueue.front();
            nodeQueue.pop();
            values.push_back(aNode->val);
            if (aNode->left) {
                nodeQueue.push(aNode->left);
            }
            if (aNode->right) {
                nodeQueue.push(aNode->right);
            }
        }
        count++;
        if (count % 2 == 0) {
            std::reverse(values.begin(), values.end());
            count %= 2;
        }
        results.emplace_back(values);
    }
    return results;
}

/* 513. Find Bottom Left Tree Value */
int findBottomLeftValue(TreeNode* root) {
    std::queue<TreeNode*> nodeQueue;
    nodeQueue.emplace(root);
    TreeNode *node = nullptr;
    while(!nodeQueue.empty()) {
        node = nodeQueue.front();
        nodeQueue.pop();
        if (node->right) {
            nodeQueue.emplace(node->right);
        }
        if (node->left) {
            nodeQueue.emplace(node->left);
        }
    }
    return node->val;
}

/* 
remaining: 
107. 二叉树的层序遍历 II https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/
104. 二叉树的最大深度 https://leetcode.cn/problems/maximum-depth-of-binary-tree/
111. 二叉树的最小深度 https://leetcode.cn/problems/minimum-depth-of-binary-tree/
2583. 二叉树中的第 K 大层和 https://leetcode.cn/problems/kth-largest-sum-in-a-binary-tree/
199. 二叉树的右视图 https://leetcode.cn/problems/binary-tree-right-side-view/
116. 填充每个节点的下一个右侧节点指针 https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/
117. 填充每个节点的下一个右侧节点指针 II https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/
1302. 层数最深叶子节点的和 https://leetcode.cn/problems/deepest-leaves-sum/
1609. 奇偶树 https://leetcode.cn/problems/even-odd-tree/
2415. 反转二叉树的奇数层 https://leetcode.cn/problems/reverse-odd-levels-of-binary-tree/
2641. 二叉树的堂兄弟节点 II https://leetcode.cn/problems/cousins-in-binary-tree-ii/
 */

/*  */