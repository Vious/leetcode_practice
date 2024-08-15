#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cstring>

/* 36. Valid Sudoku */
bool checkRow(std::vector<std::vector<char>>& board, int rIdx) {
    std::unordered_map<char, int> rMap;
    for (int i = 0; i < 9; i++) {
        if (board[rIdx][i] != '.') {
            // if (rMap.find(board[rIdx][i]) != rMap.end()) {
            //     return false;
            // } else {
            //     rMap[board[rIdx][i]]++;
            // }
            rMap[board[rIdx][i]]++;
            if (rMap[board[rIdx][i]] > 1) {
                return false;
            }
        }
    }
    return true;
}

bool checkColumn(std::vector<std::vector<char>>& board, int cIdx) {
    std::unordered_map<char, int> rMap;
    for (int i = 0; i < 9; i++) {
        if (board[i][cIdx] != '.') {
            rMap[board[i][cIdx]]++;
            // if (rMap.find(board[i][cIdx]) != rMap.end()) {
            //     return false;
            // } else {
            // }
            if (rMap[board[i][cIdx]] > 1) {
                return false;
            }
        }
    }
    return true;
}

bool checkSquare(std::vector<std::vector<char>>& board, int rIdx, int cIdx) {
    std::unordered_map<char, int> sq3Map;
    for (int i = rIdx * 3; i < rIdx * 3 + 3; i++) {
        for (int j = cIdx * 3; j < cIdx * 3 + 3; j++) {
            if (board[i][j] != '.') {
                // if (sq3Map.find(board[i][j]) != sq3Map.end()) {
                //     return false;
                // } else {
                //     sq3Map[board[i][j]]++;
                // }
                sq3Map[board[i][j]]++;
                if (sq3Map[board[i][j]] > 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isValidSudoku(std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        if (!checkRow(board, i) || !checkColumn(board, i) || !checkSquare(board, i / 3, i % 3)) {
            return false;
        }
    }
    return true;
}

/* 37. Sudoku Solver */
void solveSudoku(std::vector<std::vector<char>>& board) {

}

/* 38. Count and Say */
std::string countAndSay(int n) {
    if (n == 1) {
        return "1";
    }
    std::string result = "1";
    n--;
    while(n) {
        std::string tmpStr;
        int size = result.size();
        for (int i = 0; i < size; i++) {
            int numCount = 1;
            while(i < size - 1 && result[i] == result[i+1]) {
                numCount++;
                i++;
            }
            tmpStr += std::to_string(numCount) + result[i];
        }
        result = std::move(tmpStr);
        n--;
    }
    return result;
}

/* 39. Combination Sum */
void solvecombSumDFS(std::vector<std::vector<int>> &results, std::vector<int>& candidates, int target, std::vector<int>& curCombination, int index) {
    if (target == 0) {
        results.emplace_back(curCombination);
        return;
    } else {
        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] <= target) {
                curCombination.emplace_back(candidates[i]);
                solvecombSumDFS(results, candidates, target - candidates[i], curCombination, i);
                curCombination.pop_back();
            }
        }
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> results;
    std::vector<int> tmpCombination;
    solvecombSumDFS(results, candidates, target, tmpCombination, 0);
    return results;
}

/* 40. Combination Sum II */
void solvecombSumDFS2(std::vector<std::vector<int>> &results, std::vector<int>& candidates, int target, std::vector<int>& curCombination, int index) {
    if (target == 0) {
        results.emplace_back(curCombination);
        return;
    } else {
        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] <= target && (i == index || candidates[i] != candidates[i - 1]) ) {
                curCombination.emplace_back(candidates[i]);
                solvecombSumDFS2(results, candidates, target - candidates[i], curCombination, i + 1);
                curCombination.pop_back();
            }
        }
    }
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> results;
    std::vector<int> tmpCombination;
    std::sort(candidates.begin(), candidates.end());
    solvecombSumDFS2(results, candidates, target, tmpCombination, 0);
    return results;
}

int main()
{

    std::cout << "Testing for Problem 38. Count and Say: " << std::endl;
    std::cout << "10 : " << countAndSay(10) << std::endl;

    std::cout << "Testing for Problem 39. Combination Sum: " << std::endl;
    std::vector<int> candidates = {2,3,6,7};
    int target = 7;
    auto res = combinationSum(candidates, target);
    for (auto &aCom : res) {
        for (auto ele : aCom) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
