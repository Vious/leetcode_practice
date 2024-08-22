#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>
#include<array>

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

/* 52. N-Queens II */
bool checkCalOK(std::vector<std::vector<bool>> visited, int row, int col, int number) {
    for (int i = 0; i < number; i++) {
        if (visited[row][i] || visited[i][col]) {
            return false;
        }
        if ((row - i >= 0 && col - i >= 0 && visited[row-i][col-i] ) || (row + i < number && col + i < number && visited[row+i][col+i] ) ) {
            return false;
        }
        if ((row - i >= 0 && col + i < number && visited[row-i][col+i] ) || (row + i < number && col - i >= 0 && visited[row+i][col-i] )) {
            return false;
        }
    }
    return true;
}

void calcBacktraceNqueens(std::vector<std::vector<bool>> visited, int &count, int row, int number) {
    if (row == number) {
        count++;
        return;
    }
    for (int col = 0; col < number; col++) {
        if (checkCalOK(visited, row, col, number)) {
            visited[row][col] = true;
            calcBacktraceNqueens(visited, count, row + 1, number);
            visited[row][col] = false;
        }
    }
}

// solution 1.
// int totalNQueens(int n) {
//     std::vector<std::vector<bool>> visited(n, std::vector<bool>(n));
//     int count = 0;
//     calcBacktraceNqueens(visited, count, 0, n);

//     return count;
// }

// solution 2, a much faster solution.

void countNqueens(std::vector<bool> &cols, std::vector<bool> &left, std::vector<bool> &right, int &count, int row, int number) {
    if (row == number) {
        count++;
        return;
    }
    for (int i = 0; i < number; i++) {
        if (cols[i] || left[row+i] || right[number + row - i]) {
            continue;
        }
        cols[i] = left[row+i] = right[number + row - i] = true;
        countNqueens(cols, left, right, count, row + 1, number);
        cols[i] = left[row+i] = right[number + row - i] = false;

    }
}

int totalNQueens(int n) {
    int count = 0;
    std::vector<bool> cols(n + 1, false), left(2 * n + 1, false), right(2 * n + 1, false);
    countNqueens(cols, left, right, count, 0, n);

    return count;
}

/* 53. Maximum Subarray */


int main()
{
    std::cout << "Testing for Problem 51. N-Queens : " << std::endl;
    auto results = solveNQueens(8);
    // for(auto &aRes : results) {
    //     for (auto &aStr : aRes) {
    //         std::cout << aStr << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << results.size() << std::endl;

    std::cout << "Testing for Problem 52. N-Queens II: " << std::endl;
    std::cout << "N queens distinct results for n = 8 : " << totalNQueens(8) << std::endl;

    std::cout << "Testing for Problem 53. Maximum Subarray: " << std::endl;

    return 0;
}