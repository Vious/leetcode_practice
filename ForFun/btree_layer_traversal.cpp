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

/* 107. Binary Tree Level Order Traversal II */
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    std::vector<std::vector<int>> results;
    if (root == nullptr) {
        return results;
    }
    std::queue<TreeNode*> nodeQueue;
    std::vector<int> values;
    nodeQueue.emplace(root);
    while(!nodeQueue.empty()) {
        values.clear();
        int size = nodeQueue.size();
        for (int i = 0; i < size; i++) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            values.emplace_back(node->val);
            if (node->left) {
                nodeQueue.emplace(node->left);
            }
            if (node->right) {
                nodeQueue.emplace(node->right);
            }
        }
        results.emplace_back(values);
    }
    std::reverse(results.begin(), results.end());
    return results;
}

/* 104. Maximum Depth of Binary Tree */
int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    std::queue<TreeNode*> nodeQueue;
    nodeQueue.emplace(root);
    int count = 0;
    while(!nodeQueue.empty()) {
        int size = nodeQueue.size();
        count++;
        for (int i = 0; i < size; i++) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            if (node->left) {
                nodeQueue.emplace(node->left);
            }
            if (node->right) {
                nodeQueue.emplace(node->right);
            }
        }
    }
    return count;
}

/* 111. Minimum Depth of Binary Tree */
int minDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    std::queue<TreeNode*> nodeQueue;
    int result = INT32_MAX;
    nodeQueue.emplace(root);
    int count = 0;
    while(!nodeQueue.empty()) {
        count++;
        int size = nodeQueue.size();
        for (int i = 0; i < size; i++) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            if (node->left) {
                nodeQueue.emplace(node->left);
            }
            if (node->right) {
                nodeQueue.emplace(node->right);
            }
            if (!node->left && !node->right) {
                result = std::min(result, count);
                return result;
            }
        }
    }
    return result;
}

/* 2583. Kth Largest Sum in a Binary Tree */
long long kthLargestLevelSum(TreeNode* root, int k) {
    std::queue<TreeNode*> nodeQueue;
    std::priority_queue<long long, std::vector<long long>, std::greater<>> pQ;
    nodeQueue.emplace(root);
    while(!nodeQueue.empty()) {
        long long tmp = 0;
        int size = nodeQueue.size();
        for (int i = 0; i < size; i++) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            tmp += node->val;
            if (node->left) {
                nodeQueue.emplace(node->left);
            }
            if (node->right) {
                nodeQueue.emplace(node->right);
            }
        }
        if (pQ.size() < k) {
            pQ.push(tmp);
        } else {
            pQ.push(tmp);
            pQ.pop();
        }
    }
    if (k > pQ.size()) {
        return -1;
    }
    return pQ.top();
}

/* 199. Binary Tree Right Side View */
vector<int> rightSideView(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::vector<int> result;
    std::queue<TreeNode*> nodeQueue;
    nodeQueue.emplace(root);
    while(!nodeQueue.empty()) {
        int size = nodeQueue.size();
        result.push_back(nodeQueue.front()->val);
        for (int i = 0; i < size ; i++) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            if (node->right) {
                nodeQueue.emplace(node->right);
            }
            if (node->left) {
                nodeQueue.emplace(node->left);
            }
        }
    }
    return result;
}

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
/* 116. Populating Next Right Pointers in Each Node */
Node* connect(Node* root) {
    if (root == nullptr || (!root->left && !root->right)) {
        return root;
    }
    std::queue<Node*> nodeQueue;
    nodeQueue.emplace(root);
    while(!nodeQueue.empty()) {
        int size = nodeQueue.size();
        for (int i = 0; i < size - 1; i++) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            node->next = nodeQueue.front();
            if (node->left) {
                nodeQueue.emplace(node->left);
            }
            if (node->right) {
                nodeQueue.emplace(node->right);
            }
        }
        auto node = nodeQueue.front();
        nodeQueue.pop();
        if (node->left) {
            nodeQueue.emplace(node->left);
        }
        if (node->right) {
            nodeQueue.emplace(node->right);
        }
    }
    return root;
}

/* 117. Populating Next Right Pointers in Each Node II */
Node* connectV2(Node* root) {
    if (root == nullptr) {
        return root;
    }
    if (!root->left && !root->right) {
        root->next = nullptr;
        return root;
    }
    std::vector<Node*> nodes;
    nodes.emplace_back(root);
    while(!nodes.empty()) {
        int size = nodes.size();
        for (int i = 0; i < size - 1; i++) {
            nodes[i]->next = nodes[i + 1];
        }
        nodes[size - 1]->next = nullptr;
        std::vector<Node*> nextNodes;
        for (int i = 0; i < size; i++) {
            if (nodes[i]->left) {
                nextNodes.emplace_back(nodes[i]->left);
            }
            if (nodes[i]->right) {
                nextNodes.emplace_back(nodes[i]->right);
            }
        }
        nodes = std::move(nextNodes);
    }
    return root;
}

/* 1302. Deepest Leaves Sum */
int deepestLeavesSum(TreeNode* root) {
    if (!root->left && !root->right) {
        return root->val;
    }
    std::vector<TreeNode*> nodes;
    int sum = 0;
    nodes.emplace_back(root);
    while(!nodes.empty()) {
        int size = nodes.size();
        std::vector<TreeNode*> tmpNodes;
        for (int i = 0 ; i < size ; i++) {
            if (nodes[i]->left) {
                tmpNodes.emplace_back(nodes[i]->left);
            }
            if (nodes[i]->right) {
                tmpNodes.emplace_back(nodes[i]->right);
            }
        }
        if (tmpNodes.empty()) {
            for (int i = 0 ; i < size ; i++) {
                sum += nodes[i]->val;
            }
        }
        nodes = std::move(tmpNodes);
    }
    return sum;
}

/* 1609. Even Odd Tree */
bool isEvenOddTree(TreeNode* root) {
    if (!root->left && !root->right) {
        return root->val % 2 == 1;
    }
    std::vector<TreeNode*> nodes;
    nodes.emplace_back(root);
    int count = 0;
    while(!nodes.empty()) {
        int size = nodes.size();
        for (int i = 0; i < size - 1; i++) {
            if (count % 2 == 0) {
                if (nodes[i]->val >= nodes[i + 1]->val || nodes[i]->val % 2 == 0 || nodes[i+1]->val % 2 == 0) {
                    return false;
                }
            } else {
                if (nodes[i]->val <= nodes[i + 1]->val || nodes[i]->val % 2 == 1 || nodes[i+1]->val % 2 == 1) {
                    return false;
                }
            }
        }
        if (size == 1) {
            if (count % 2 == 0) {
                if (nodes[0]->val % 2 == 0) return false;
            } else {
                if (nodes[0]->val % 2 == 1) return false;
            }
        }
        std::vector<TreeNode*> tmpNodes;
        for (int i = 0; i < size; i++) {
            if (nodes[i]->left) {
                tmpNodes.emplace_back(nodes[i]->left);
            }
            if (nodes[i]->right) {
                tmpNodes.emplace_back(nodes[i]->right);
            }
        }
        nodes = std::move(tmpNodes);
        count++;
        count %= 2;
    }
    return true;
}

/* 2415. Reverse Odd Levels of Binary Tree */
TreeNode* reverseOddLevels(TreeNode* root) {
    if (!root || (!root->left && !root->right)) {
        return root;
    }
    std::vector<TreeNode*> nodes;
    nodes.emplace_back(root);
    int count = 0;
    while(!nodes.empty()) {
        int size = nodes.size();
        if (count % 2 == 1) {
            for (int i = 0; i < size / 2; i++) {
                std::swap(nodes[i]->val, nodes[size - 1 - i]->val);
            }
        }
        std::vector<TreeNode*> tmpNodes;
        for (int i = 0; i < size; i++) {
            if (nodes[i]->left) {
                tmpNodes.emplace_back(nodes[i]->left);
            }
            if (nodes[i]->right) {
                tmpNodes.emplace_back(nodes[i]->right);
            }
        }
        nodes = std::move(tmpNodes);
        count++;
        count %= 2;
    }
    return root;
}

/* 2641. Cousins in Binary Tree II */
/* refer to : https://leetcode.cn/problems/cousins-in-binary-tree-ii/solutions/2229010/bfssuan-liang-ci-pythonjavacgo-by-endles-b72a/ */
TreeNode* replaceValueInTree(TreeNode* root) {
    /* 对于一个节点 x 来说，它的所有堂兄弟节点值的和，等于 x 这一层的所有节点值之和减去 x 及其兄弟节点的值之和。 */
    root->val = 0;
    std::vector<TreeNode*> nodes;
    nodes.emplace_back(root);
    while(!nodes.empty()) {
        int nextLevelSum = 0;
        std::vector<TreeNode*> nextNodes;
        for (auto aNode : nodes) {
            if (aNode->left) {
                nextLevelSum += aNode->left->val;
                nextNodes.emplace_back(aNode->left);
            }
            if (aNode->right) {
                nextLevelSum += aNode->right->val;
                nextNodes.emplace_back(aNode->right);
            }
        }

        for (auto aNode : nodes) {
            // int tmpSum = (aNode->left ? aNode->left->val : 0) + (aNode->right? aNode->right->val : 0);
            int tmpSum = 0;
            if (aNode->left) {
                tmpSum += aNode->left->val;
            }
            if (aNode->right) {
                tmpSum += aNode->right->val;
            }
            if (aNode->left) {
                aNode->left->val = nextLevelSum - tmpSum;
            }
            if (aNode->right) {
                aNode->right->val = nextLevelSum - tmpSum;
            }
        }
        nodes = std::move(nextNodes);
    }
    return root;
}