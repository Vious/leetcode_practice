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

int main()
{



    return 0;
}
