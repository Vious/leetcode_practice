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
/* !!! NO need a for loop */
vector<string> letterCasePermutation(string s) {
    int size = s.size();
    std::vector<std::string> results;
    if (size == 0) {
        return results;
    }
    std::function<void(std::string, int)> dfs = [&](std::string str, int depth) {
        if (depth == size) {
            results.emplace_back(str);
            return;
        }
        int i = depth;
        if (s[i] >= 'A' && s[i] <= 'Z' ) {
            char lowerCh = std::tolower(s[i]);
            dfs(str + lowerCh, i + 1);
            dfs(str + s[i], i + 1);
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            char upperCh = std::toupper(s[i]);
            dfs(str + upperCh, i + 1);
            dfs(str + s[i], i + 1);
        } else {
            dfs(str + s[i], i + 1);
        }

    };
    dfs("", 0);
    return results;
}

/* LCP 51. 烹饪料理 */
int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit) {
    int result = -1, limitSum = 0;
    int size = cookbooks.size();
    int materSize = materials.size();
    std::function<void(int, int)> calDFS = [&](int level, int sum) {
        if (level == size) {
            if (limitSum >= limit) {
                result = std::max(result, sum);
            }
            return;
        }
        auto aBook = cookbooks[level];
        bool canMake = true;
        for (int i = 0; i < materSize; i++) {
            if (materials[i] < aBook[i]) {
                canMake = false;
                break;
            }
        }
        if (canMake) {
            sum += attribute[level][0];
            limitSum += attribute[level][1];
            for (int i = 0; i < materSize; i++) {
                materials[i] -= aBook[i];
            }
            calDFS(level + 1, sum);
            sum -= attribute[level][0];
            limitSum -= attribute[level][1];
            for (int i = 0; i < materSize; i++) {
                materials[i] += aBook[i];
            }
            calDFS(level + 1, sum);
        } else {
            calDFS(level + 1, sum);
        }
    };
    calDFS(0, 0);
    return result;
}

/* 2397. Maximum Rows Covered by Columns */
int maximumRows(vector<vector<int>>& matrix, int numSelect) {
    int m = matrix.size(), n = matrix[0].size();
    int result = 0;
    std::function<int(std::vector<int>)> cntCovered = [&](std::vector<int> cols) {
        int ans = 0;
        for (int i = 0; i < m; i++) {
            bool zeroFlag = true;
            bool covFlag = true;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    zeroFlag = false;
                    bool tmpFlag = false;
                    for (auto val : cols) {
                        if (val == j) {
                            tmpFlag = true;
                        }
                    }
                    if (tmpFlag == false) {
                        covFlag = false;
                        break;
                    }
                }
            }
            if (zeroFlag) {
                ans++;
            } else if (covFlag) {
                ans++;
            }
        }
        return ans;
    };
    std::function<void(int, std::vector<int>)> rowBacktrace = [&](int num, std::vector<int> cols) {
        if (num == n || cols.size() == numSelect) {
            int curCovered = cntCovered(cols);
            result = std::max(result, curCovered);
            return;
        }
        rowBacktrace(num + 1, cols);
        cols.push_back(num);
        rowBacktrace(num + 1, cols);
    };
    std::vector<int> selectCols;
    rowBacktrace(0, selectCols);
    return result;
}

/* 1239. Maximum Length of a Concatenated String with Unique Characters */
int maxLength(vector<string>& arr) {
    /* check duplicate logic could be replaced by hash or bits compression */
    int size = arr.size();
    int result = 0;
    std::function<void(int, std::string)> dfs = [&](int num, std::string str) {
        if (num == size) {
            result = std::max(result, (int)str.size());
            return;
        }
        bool unqFlag = true;
        for (char ch : arr[num]) {
            for (char s : str) {
                if (ch == s) {
                    unqFlag = false;
                    break;
                }
            }
        }
        bool selfUniq = true;
        for (int i = 0; i < arr[num].size(); i++) {
            for (int j = i + 1; j < arr[num].size(); j++) {
                if (arr[num][i] == arr[num][j]) {
                    selfUniq = false;
                    break;
                }
            }
        }
        if (!unqFlag || !selfUniq) {
            dfs(num + 1, str);
        } else {
            dfs(num + 1, str);
            dfs(num + 1, str + arr[num]);
        }
    };
    dfs(0, "");
    return result;
}

/* 2212. Maximum Points in an Archery Competition */
vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
    std::vector<int> result(12, 0);
    int maxPoint = INT32_MIN;
    std::vector<int> tmpTry(12, 0);
    std::function<void(int, int, int)> tryDFS = [&](int num, int tmpSum, int remain) {
        if (num == aliceArrows.size() || remain == 0) {
            if (tmpSum > maxPoint) {
                maxPoint = tmpSum;
                // random add remain to a try
                tmpTry[11] += remain;
                result = tmpTry;
                // tmpTry[11] -= remain;
            }
            return;
        }
        if (aliceArrows[num] < remain) {
            tmpTry[num] = aliceArrows[num] + 1;
            tryDFS(num + 1, tmpSum + num, remain - tmpTry[num]);
            tmpTry[num] = 0;
        }
        tryDFS(num + 1, tmpSum, remain);
    };
    tryDFS(0, 0, numArrows);
    return result;
}

/* 2698. Find the Punishment Number of an Integer */
int punishmentNumber(int n) {
    std::function<bool(std::vector<int>&, int, int, int, int)> dfsCheck = \
        [&](std::vector<int>& digit, int left, int depth, int sum, int target) -> bool {
            if (depth == digit.size()) {
                if (left < depth) {
                    int tmpSum = 0;
                    for (int i = left; i < digit.size(); i++) {
                        tmpSum = tmpSum * 10 + digit[i];
                    }
                    sum += tmpSum;
                }
                if (sum == target) {
                    return true;
                } else {
                    return false;
                }
            }
            int tmpSum = 0;
            for (int i = left; i <= depth; i++) {
                tmpSum = tmpSum * 10 + digit[i];
            }
            bool split = dfsCheck(digit, depth + 1, depth + 1, sum + tmpSum, target);
            bool notSplit = dfsCheck(digit, left, depth + 1, sum, target);
            return split || notSplit;
    };
    std::vector<int> digits;
    int result = 0;
    for (int i = 1; i <= n; i++) {
        int val = i * i;
        digits.clear();
        while(val > 0) {
            digits.push_back(val % 10);
            val /= 10;
        }
        std::reverse(digits.begin(), digits.end());
        if (dfsCheck(digits, 0, 0, 0, i)) {
            result += i * i;
        }
    }
    return result;
}

/* 306. Additive Number */
bool isAdditiveNumber(string num) {
    /* learned from deepseek, very good!!! */
    int size = num.size();
    std::function<std::string(std::string, std::string)> addString = [](std::string num1, std::string num2) {
        std::string result;
        int carry = 0;
        int i = num1.length() - 1, j = num2.length() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }
        std::reverse(result.begin(), result.end());
        return result;
    };
    std::function<bool(std::string, std::string, std::string)> checkValid = 
    [&](std::string num1, std::string num2, std::string remain) {
        if (remain.empty()) {
            return true;
        }
        std::string sum = addString(num1, num2);
        if (sum == remain.substr(0, sum.size())) {
            return checkValid(num2, sum, remain.substr(sum.size()));
        }
        return false;
    };
    for (int i = 1; i <= size / 2; i++) {
        for (int j = 1; j <= (size - i) / 2; j++) {
            std::string num1Str = num.substr(0, i);
            std::string num2Str = num.substr(i, j);
            if ((num1Str.size() > 1 && num1Str[0] == '0') || (num2Str.size() > 1 && num2Str[0] == '0')) {
                if(num1Str.size() > 1 && num1Str[0] == '0') {
                    break;
                }
                continue;
            }
            if (checkValid(num1Str, num2Str, num.substr(i + j))) {
                return true;
            }
        }
    }
    return false;
}

/* 93. Restore IP Addresses */
bool isValid(std::string part) {
    if (part.size() > 1 && part[0] == '0') return false;
    if (part.size() > 3 || part.empty()) return false;
    int num = std::stoi(part);
    return num >= 0 && num <= 255;
}

void backtrace(std::string &str, int depth, int num, std::string curStr, std::vector<std::string> &results) {
    if (num == 4) {
        if (depth == str.size()) {
            results.emplace_back(curStr);
        }
        return;
    }
    for (int i = 1; i <= 3 && i + depth <= str.size(); i++) {
        std::string tmpStr = str.substr(depth, i);
        if (isValid(tmpStr)) {
            backtrace(str, depth + i, num + 1, curStr + (num == 0 ? "" : ".") + tmpStr, results);
        }
    }
}
vector<string> restoreIpAddresses(string s) {
    std::vector<std::string> results;
    backtrace(s, 0, 0, "", results);
    return results;
}


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

    std::cout << "Test 784. Letter Case Permutation s = a1b2" << std::endl;
    auto res2 = letterCasePermutation("a1b2");
    for (auto str : res2) {
        std::cout << str << ", ";
    } 
    std::cout << std::endl;
    std::cout << "Test 784. Letter Case Permutation s = 3z4" << std::endl;
    auto res3 = letterCasePermutation("3z4");
    for (auto str : res3) {
        std::cout << str << ", ";
    } 
    std::cout << std::endl;

    std::vector<std::vector<int>> matrix1 = {{0,0,1},{1,0,0},{0,0,0}};
    std::vector<std::vector<int>> matrix2 = {{0,0,0},{1,0,1},{0,1,1},{0,0,1}};
    std::cout << "Test 2397. Maximum Rows Covered by Columns: " << maximumRows(matrix1, 2) << std::endl;
    std::cout << "Test 2397. Maximum Rows Covered by Columns: " << maximumRows(matrix2, 2) << std::endl;

    std::cout << "Test 2698. Find the Punishment Number of an Integern, n = 10 : " << punishmentNumber(10) << std::endl;


    return 0;
}