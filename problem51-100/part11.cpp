#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>

/* 51. N-Queens */
bool checkPositionOK(std::vector<std::string> &tmpResult, int row, int col) {
    int size = tmpResult.size();
    for (int i  = 0; i < size; i++) {
        if (tmpResult[row][i] != '.' || tmpResult[i][col] != '.') {
            return false;
        }
        if ((row - i >= 0 && col - i >= 0 && tmpResult[row-i][col-i] != '.') || (row + i < size && col + i < size && tmpResult[row+i][col+i] != '.') ) {
            return false;
        }
        if ((row - i >= 0 && col + i < size && tmpResult[row-i][col+i] != '.') || (row + i < size && col - i >= 0 && tmpResult[row+i][col-i] != '.') ) {
            return false;
        }
    }
    return true;
}

void backtracNQueens(std::vector<std::vector<std::string>> &results, std::vector<std::string> &tmpResult, int row, int number) {
    if (row == number) {
        results.emplace_back(tmpResult);
        return;
    }
    for (int col = 0; col < number; col++) {
        if (checkPositionOK(tmpResult, row, col)) {
            tmpResult[row][col] = 'Q';
            backtracNQueens(results, tmpResult, row + 1, number);
            tmpResult[row][col] = '.';
        }
    }
}

std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> results;
    std::vector<std::string> tmpResult(n, std::string(n, '.'));
    backtracNQueens(results, tmpResult, 0, n);

    return results;
}

int main()
{
    std::cout << "Testing for Problem 51. N-Queens : " << std::endl;
    auto results = solveNQueens(8);
    for(auto &aRes : results) {
        for (auto &aStr : aRes) {
            std::cout << aStr << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << results.size() << std::endl;


    return 0;
}