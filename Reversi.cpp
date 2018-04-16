//
// Created by DFZ on 2018/4/12.
//

#include "Reversi.h"
#include <algorithm>
#include <iostream>

Reversi::Reversi() {
    board[0].fill(0);
    board.fill(board[0]);
    board[3][3] = WHITE;
    board[4][4] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
}

std::array<std::array<int, 8>, 8> Reversi::getBoard() {
    return board;
}

bool Reversi::isValid(int row, int column, int color) {
    for (int i = 0; i < 8; i++) {
        if (i != row && i != row - 1 && i != row + 1 && board[i][column] == color) {
            int flag = 0;
            for (int j = std::min(i, row) + 1; j < std::max(i, row); j++) {
                if (board[j][column] == -color) {
                    continue;
                } else {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                return true;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        if (i != column && i != column - 1 && i != column + 1 && board[column][i] == color) {
            int flag = 0;
            for (int j = std::min(i, column) + 1; j < std::max(i, column); j++) {
                if (board[row][j] == -color) {
                    continue;
                } else {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                return true;
            }
        }
    }

    for (int i = 0; i < row + column; i++) {
        if (i != row && i != row - 1 && i != row + 1 && board[i][row + column - i] == color) {
            int flag = 0;
            for (int j = std::min(i, row) + 1; j < std::max(i, row); j++) {
                if (board[i][row + column - i] == -color) {
                    continue;
                } else {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::next(int row, int column, int color) {
    if (!isValid(row, column, color)) {
        std::cerr << "invalid move" << std::endl;
        return;
    }

    for (int i = 0; i < 8; ++i) {
        if (canFlip(i, column, row, column)) {
            flip(i, column, row, column);
        }
    }

    for (int i = 0; i < 8; ++i) {
        if (canFlip(row, i, row, column)) {
            flip(row, i, row, column);
        }
    }


    for (int i = 0; i < row + column; ++i) {
        if (canFlip(row + column - i, i, row, column)) {
            flip(row + column - i, i, row, column);
        }
    }

}

bool Reversi::canFlip(int row1, int column1, int row2, int column2) {
    if (row1 == row2) {
        int min = std::min(column1, column2);
        int max = std::max(column1, column2);
        if (max - min <= 1 || board[row1][max] != board[row2][min]) {
            return false;
        }
        int color = board[row1][max];
        for (int i = min + 1; i < max; i++) {
            if (board[row1][i] == color) {
                return false;
            }
        }
        return true;
    }

    if (column1 == column2) {
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);
        if (max - min <= 1 || board[max][column1] != board[min][column2]) {
            return false;
        }
        int color = board[max][column1];
        for (int i = min + 1; i < max; i++) {
            if (board[i][column1] == color) {
                return false;
            }
        }
        return true;
    }

    if (row1 + column1 == row2 + column2) {
        int sum = row1 + column1;
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);
        if (max - min <= 1 || board[min][sum - min] != board[max][sum - max]) {
            return false;
        }
        int color = board[max][sum - min];
        for (int i = min + 1; i < max; i++) {
            if (board[i][sum - i] == color) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void Reversi::flip(int row1, int column1, int row2, int column2) {
    if (row1 == row2) {
        int min = std::min(column1, column2);
        int max = std::max(column1, column2);

        int color = board[row1][max];
        for (int i = min + 1; i < max; i++) {
            board[row1][i] = -color;
        }
        return;
    }

    if (column1 == column2) {
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);

        int color = board[max][column1];
        for (int i = min + 1; i < max; i++) {
            board[i][column1] = -color;
        }
        return;
    }

    if (row1 + column1 == row2 + column2) {
        int sum = row1 + column1;
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);

        int color = board[max][sum - min];
        for (int i = min + 1; i < max; i++) {
            board[i][sum - i] = -color;
        }
        return;
    }
}
