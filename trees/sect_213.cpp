#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>
#include <cmath>
#include <sstream>
#include <functional>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 993. Cousins in Binary Tree */
bool isCousins(TreeNode* root, int x, int y) {
    int depth = 0;
    TreeNode *parent = nullptr;
    std::function<bool(TreeNode *node, TreeNode *pr, int dep)> cousinsDFS = [&](TreeNode *node, TreeNode *pr, int dep) -> bool {
        if (node == nullptr) {
            return false;
        }  
        if (node->val == x or node->val == y) {
            if (depth) {
                return depth == dep && parent != pr;
            }
            depth = dep;
            parent = pr;
        }
        return cousinsDFS(node->left, node, dep + 1) || cousinsDFS(node->right, node, dep + 1);
    };
    return cousinsDFS(root, nullptr, 1);
}

/*  */

int main()
{

    return 0;
}