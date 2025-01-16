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
/* binary search tree */

/* Definition for singly-linked list. */ 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 98. Validate Binary Search Tree */
bool isValidBST(TreeNode* root) {
    std::function<bool(TreeNode*, long long, long long)> checkBstDFS;
    checkBstDFS = [&](TreeNode* node, long long left, long long right) -> bool {
        if (node == nullptr) {
            return true;
        }
        int val = node->val;
        return left < val and val < right && checkBstDFS(node->left, left, val) && checkBstDFS(node->right, val, right);
    };
    return checkBstDFS(root, INT64_MIN, INT64_MAX);
}

/* 700. Search in a Binary Search Tree */
TreeNode* searchBST(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    int value = root->val;
    if (value == val) {
        return root;
    } else if (val > root->val) {
        return searchBST(root->right, val);
    } else {
        return searchBST(root->left, val);
    }
}

/* 938. Range Sum of BST */
int rangeSumBST(TreeNode* root, int low, int high) {
    if(root == nullptr) {
        return 0;
    }
    if (root->left == root->right) {
        return (low <= root->val && root->val <= high) ? root->val : 0;
    }
    int sum = 0;
    if (low <= root->val && root->val <= high) {
        sum += root->val;
    }
    if (root->val > low) {
        sum += rangeSumBST(root->left, low, high);
    }
    if (root->val < high) {
        sum += rangeSumBST(root->right, low, high);
    }
    return sum;
}

/* 530. Minimum Absolute Difference in BST */
int getMinimumDifference(TreeNode* root) {
    std::function<void(TreeNode*, std::vector<int>&)> inorderDFS;
    inorderDFS = [&](TreeNode* node, std::vector<int>& values) {
        if(node == nullptr) {
            return;
        }
        inorderDFS(node->left, values);
        values.push_back(node->val);
        inorderDFS(node->right, values);
    };
    std::vector<int> nodeValues;
    inorderDFS(root, nodeValues);
    int minDiff = INT32_MAX;
    int size = nodeValues.size();
    for (int i = 1; i < size; i++) {
        minDiff = std::min(minDiff, nodeValues[i] - nodeValues[i-1]);
    }
    return minDiff;
}

/* 2476. Closest Nodes Queries in a Binary Search Tree */
vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
    std::vector<vector<int>> results;
    std::vector<int> values;
    std::function<void(TreeNode*)> inorderDFS;
    inorderDFS = [&](TreeNode *node) {
        if (node == nullptr) {
            return;
        }
        inorderDFS(node->left);
        values.push_back(node->val);
        inorderDFS(node->right);
    };
    inorderDFS(root);
    int size = queries.size();
    for (int i = 0; i < size; i++) {
        int indx = std::ranges::lower_bound(values, queries[i]) - values.begin();
        int right = indx < values.size() ? values[indx] : -1;
        if (indx == values.size() || values[indx] != queries[i]) {
            indx--;
        }
        int left = indx >= 0 ? values[indx] : -1;
        results.push_back({left, right});
    }
    return results;
}

/* 501. Find Mode in Binary Search Tree */
vector<int> findMode(TreeNode* root) {
    std::vector<int> results;
    std::unordered_map<int, int> cntMap;
    std::function<void(TreeNode*)> findModeDFS;
    findModeDFS = [&](TreeNode *node) {
        if (node == nullptr) {
            return;
        } 
        findModeDFS(node->left);
        cntMap[node->val]++;
        findModeDFS(node->right);
    };
    findModeDFS(root);
    std::vector<std::pair<int, int>> v2fPair;
    for (auto iter = cntMap.begin(); iter != cntMap.end(); iter++) {
        v2fPair.emplace_back(std::make_pair(iter->second, iter->first));
    }
    std::sort(v2fPair.begin(), v2fPair.end(), std::greater<>());
    int freq = INT32_MIN;
    for (auto pair : v2fPair) {
        if (freq <= pair.first) {
            results.push_back(pair.second);
            freq = pair.first;
        } else {
            break;
        }
    }
    return results;
}

/* 230. Kth Smallest Element in a BST */
int kthSmallest(TreeNode* root, int k) {
    std::vector<int> values;
    std::function<void(TreeNode*)> inorderDFS;
    inorderDFS = [&](TreeNode *node) {
        if (node == nullptr) {
            return;
        }
        inorderDFS(node->left);
        values.push_back(node->val);
        inorderDFS(node->right);
    };
    inorderDFS(root);
    return values[k - 1];
}

/* 1373. Maximum Sum BST in Binary Tree */
int maxSumBST(TreeNode* root) {
    int result;
    std::function<std::tuple<int,int,int>(TreeNode*)> treeDFS;
    treeDFS = [&](TreeNode *node) -> std::tuple<int,int,int> {
        if (node == nullptr) {
            return {INT32_MAX, INT32_MIN, 0};
        }
        auto [leftMin, LeftMax, leftSum] = treeDFS(node->left);
        auto [rightMin, rightMax, rightSum] = treeDFS(node->right);
        int val = node->val;
        if (val <= LeftMax || val >= rightMin) {
            return {INT32_MIN, INT32_MAX, 0};
        }
        int sum = leftSum + rightSum + val;
        result = std::max(result, sum);
        
        return {std::min(leftMin, val), std::max(rightMax, val), sum};
    };
    treeDFS(root);
    return result;
}

/* 105. Construct Binary Tree from Preorder and Inorder Traversal */
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty()) {
        return nullptr;
    }
    int leftSize = std::find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();
    std::vector<int> preLeft(preorder.begin() + 1, preorder.begin() + leftSize + 1);
    std::vector<int> preRight(preorder.begin() + 1 + leftSize, preorder.end());

    std::vector<int> inLeft(inorder.begin(), inorder.begin() + leftSize);
    std::vector<int> inRight(inorder.begin() + leftSize + 1, inorder.end());

    TreeNode *leftTree = buildTree(preLeft, inLeft);
    TreeNode *rightTree = buildTree(preRight, inRight);
    return new TreeNode(preorder[0], leftTree, rightTree);
}

/* 106. Construct Binary Tree from Inorder and Postorder Traversal */
TreeNode* buildTreeV2(vector<int>& inorder, vector<int>& postorder) {
    if (postorder.empty()) {
        return nullptr;
    }
    int rootVal = postorder[postorder.size() - 1];
    int leftIndx = std::find(inorder.begin(), inorder.end(), rootVal) - inorder.begin();

    std::vector<int> inLeft(inorder.begin(), inorder.begin() + leftIndx);
    std::vector<int> inRight(inorder.begin() + leftIndx + 1, inorder.end());

    std::vector<int> postLeft(postorder.begin(), postorder.begin() + leftIndx);
    std::vector<int> postRight(postorder.begin() + leftIndx, postorder.end() - 1);

    TreeNode *leftTree = buildTreeV2(inLeft, postLeft);
    TreeNode *rightTree = buildTreeV2(inRight, postRight);

    return new TreeNode(rootVal, leftTree, rightTree);
}

/* 889. Construct Binary Tree from Preorder and Postorder Traversal */
TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    if (preorder.empty()) {
        return nullptr;
    }
    if (preorder.size() == 1) {
        return new TreeNode(preorder[0]);
    }
    int rootVal = preorder[0];

    int leftIndx = std::find(postorder.begin(), postorder.end(), preorder[1]) - postorder.begin() + 1;
    std::vector<int> preLeft(preorder.begin() + 1, preorder.begin() + leftIndx + 1);
    std::vector<int> preRight(preorder.begin() + leftIndx + 1, preorder.end());

    std::vector<int> postLeft(postorder.begin(), postorder.begin() + leftIndx);
    std::vector<int> postRight(postorder.begin() + leftIndx, postorder.end() - 1);

    TreeNode *leftTree = constructFromPrePost(preLeft, postLeft);
    TreeNode *rightTree = constructFromPrePost(preRight, postRight);
    return new TreeNode(rootVal, leftTree, rightTree);
}

/* 1110. Delete Nodes And Return Forest */
vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    std::vector<TreeNode*> results;
    std::set<int> nodeValSet;
    for (auto val : to_delete) {
        nodeValSet.insert(val);
    }
    std::function<TreeNode*(TreeNode*)> postorderDFS;
    postorderDFS = [&](TreeNode *node) -> TreeNode* {
        if (node == nullptr) {
            return nullptr;
        }
        node->left = postorderDFS(node->left);
        node->right = postorderDFS(node->right);
        if (!nodeValSet.count(node->val)) {
            return node;
        }
        if(node->left) {
            results.emplace_back(node->left);
        }
        if (node->right) {
            results.emplace_back(node->right);
        }
        return nullptr;
    };
    if(postorderDFS(root)) {
        results.emplace_back(root);
    }
    return results;
}