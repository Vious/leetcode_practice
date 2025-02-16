#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>
#include <set>
#include <stack>

/* 
v2 : combination type backtracking, cutting edge
*/
using namespace std;

/* 77. Combinations */
vector<vector<int>> combine(int n, int k) {
    std::vector<std::vector<int>> results;
    std::vector<int> path;
    std::function<void(int)> dfsCombine = [&](int depth) {
        if (path.size() + depth < k) {
            return;
        }
        if (path.size() == k) {
            results.push_back(path);
            return;
        }
        for (int i = depth; i >= 1; i--) {
            path.push_back(i);
            /* !!! should be i - 1 */
            dfsCombine(i - 1);
            path.pop_back();
        }
    };
    dfsCombine(n);
    return results;
}

/* 216. Combination Sum III */
vector<vector<int>> combinationSum3(int k, int n) {
    std::vector<std::vector<int>> results;
    std::vector<int> path;
    std::function<void(int, int)> dfsCombineSum = [&](int depth, int target) {
        int len = k - path.size();
        // target < 0 or target > sum of remaining
        if (len > depth || target < 0 || (target > (depth * 2 - len + 1) * len / 2)) {
            return;
        }
        if (path.size() == k) {
            results.push_back(path);
            return;
        }
        for (int i = depth; i >= 1; i--) {
            path.push_back(i);
            /* !!! should be i - 1 */
            dfsCombineSum(i - 1, target - i);
            path.pop_back();
        }
    };
    if (n <= 9) {
        dfsCombineSum(n, n);
    } else {
        dfsCombineSum(9, n);
    }
    return results;
}

/* 22. Generate Parentheses */
vector<string> generateParenthesis(int n) {
    std::vector<std::string> results;
    std::function<void(int, int, std::string)> dfsGen = [&](int left, int right, std::string str) {
        if (right == n) {
            results.emplace_back(str);
            return;
        }
        if (left <= right) {
            dfsGen(left + 1, right, str + "(");
        } else {
            if (left < n) {
                dfsGen(left + 1, right, str + "(");
                dfsGen(left, right + 1, str + ")");
            } else {
                dfsGen(left, right + 1, str + ")");
            }
        }
    };
    dfsGen(0, 0, "");
    return results;
}

/* 301. Remove Invalid Parentheses */
/* need to find a better solution */
vector<string> removeInvalidParentheses(string s){
    std::vector<std::string> results;
    int leftCnt = 0, rightCnt = 0;
    int size = s.size();
    std::set<std::string> uniSet;
    std::stack<char> myStack;
    std::string tmpStr = "";
    int validLength = 0;
    for (int i = 0; i < size; i++) {
        if (s[i] == '(') {
            leftCnt++;
            myStack.push(s[i]);
        } else if (s[i] == ')'){
            rightCnt++;
            if (!myStack.empty()) {
                myStack.pop();
                validLength++;
            }
        } else {
            tmpStr += s[i];
        }
    }
    /* needs to fix bugs */
    std::function<void(int, int, int, std::string)> dfsRemove = [&](int left, int right, int depth, std::string curStr) {
        if (depth == size) {
            if (right == left && right == validLength) {
                uniSet.insert(curStr);
            }
            return;
        }
        if (right == validLength && left == right) {
            for (int i = depth; i < size; i++) {
                if (s[i] != '(' && s[i] != ')') {
                    curStr += s[i];
                }
            }
            uniSet.insert(curStr);
            return;
        }
        if (s[depth] != '(' && s[depth] != ')') {
            dfsRemove(left, right, depth + 1, curStr + s[depth]);
        } else {
            if (s[depth] == '(') {
                dfsRemove(left + 1, right, depth + 1, curStr + s[depth]);
                dfsRemove(left, right, depth + 1, curStr);
            } else {
                if (left > right) {
                    dfsRemove(left, right + 1, depth + 1, curStr + s[depth]);
                    dfsRemove(left, right, depth + 1, curStr);
                } else {
                    dfsRemove(left, right, depth + 1, curStr);
                }
            }
        }
    };
    dfsRemove(0, 0, 0, "");
    if (uniSet.empty() || validLength == 0) {
        results.push_back(tmpStr);
    } else {
        for (auto iter = uniSet.begin(); iter != uniSet.end(); iter++) {
            results.emplace_back(*iter);
        }    
    }
    return results;
}

/* 39. Combination Sum */
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    std::vector<std::vector<int>> results;
    int size = candidates.size();
    std::vector<int> path;
    std::function<void(int, int)> dfsCombineSum = [&](int depth, int curTarget) {
        // curTarget < 0
        if (curTarget < 0) {
            return;
        }
        if (curTarget == 0) {
            results.emplace_back(path);
            return;
        }
        for (int i = depth; i >= 0; i--) {
            path.push_back(candidates[i]);
            dfsCombineSum(i, curTarget - candidates[i]);
            path.pop_back();
        }
    };
    std::sort(candidates.begin(), candidates.end(), std::greater<>());
    dfsCombineSum(size - 1, target);
    return results;
}


int main()
{
    std::cout << "Test 77. Combinations (n = 4, k = 2): " << std::endl;
    auto res1 = combine(4, 2);
    for (auto vec : res1) {
        for (int ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Test 301. Remove Invalid Parentheses s = )()(: " << std::endl;
    auto res2 = removeInvalidParentheses(")()(");
    for (auto str : res2) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::cout << "Test 301. Remove Invalid Parentheses s = (()y: " << std::endl;
    auto res3 = removeInvalidParentheses("(()y");
    for (auto str : res3) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::cout << "Test 301. Remove Invalid Parentheses s = (((k()((: " << std::endl;
    auto res4 = removeInvalidParentheses("(((k()((");
    for (auto str : res4) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}