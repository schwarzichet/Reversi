//
// Created by DFZ on 2018/4/12.
//

#include "Reversi.h"
#include <algorithm>
#include <iostream>
#include <assert.h>

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
    if (board[row][column] != 0) {
        return false;
    }
    board[row][column] = color;
    for (int i = 0; i < 8; i++) {
        if (i != row && i != row - 1 && i != row + 1 && board[i][column] == color) {
            if (canFlip(i, column, row, column)) {
                board[row][column] = 0;
                //std::cerr << "valid in column" << std::endl;
                return true;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        if (i != column && i != column - 1 && i != column + 1 && board[row][i] == color) {
            if (canFlip(row, i, row, column)) {
                //std::cerr << "valid in row" << std::endl;
                board[row][column] = 0;
                return true;
            }
        }
    }

    for (int i = 0; i <= row + column && i < 8; i++) {
        if (row + column - i >= 8) {
            continue;
        }
        if (i != row && i != row - 1 && i != row + 1 && board[i][row + column - i] == color) {
            if (canFlip(row, column, i, row + column - i)) {
                //std::cerr << "valid in right diagnose" << std::endl;
                board[row][column] = 0;
                return true;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        if (column - row + i >= 8 || column - row + i < 0) {
            continue;
        }
        if (i != row && i != row - 1 && i != row + 1 && board[i][column - row + i] == color) {
            if (canFlip(row, column, i, column - row + i)) {
                //std::cerr << "valid in left diagnose" << std::endl;
//                std::cerr << "row:" << i << "column" << column - row + i << std::endl;
                board[row][column] = 0;
                return true;
            }
        }
    }
    board[row][column] = 0;
    return false;
}

Reversi Reversi::next(int row, int column, int color) {
    Reversi r = Reversi(*this);

    if (!r.isValid(row, column, color)) {
        std::cerr << "invalid move" << std::endl;
        return r;
    }

    r.board[row][column] = color;
    for (int i = 0; i < 8; ++i) {
        if (r.canFlip(i, column, row, column)) {
            //std::cout << "can flip:" << i << " " << column << std::endl;
            r.flip(i, column, row, column);
        }
    }

    for (int i = 0; i < 8; ++i) {
        if (r.canFlip(row, i, row, column)) {
            //std::cout << "can flip:" << row << " "<< i << std::endl;

            r.flip(row, i, row, column);
        }
    }


    for (int i = 0; i <= row + column; ++i) {
        if (r.canFlip(row + column - i, i, row, column)) {
            //std::cout << "can flip:" << row + column - i << " "<< i << std::endl;

            r.flip(row + column - i, i, row, column);
        }
    }

    for (int i = 0; i <= 8; ++i) {
        if (r.canFlip(i, i - row + column, row, column)) {
            //std::cout << "can flip:" << i << " "<< i - row + column << std::endl;
            r.flip(i, i - row + column, row, column);
        }
    }
    return r;
}

bool Reversi::canFlip(int row1, int column1, int row2, int column2) {
    if (row1 >= 8 || row1 < 0 || row2 >= 8 || row2 < 0 || column1 >= 8 || column1 < 0 || column2 >= 8 || column2 < 0) {
        return false;
    }

    if (row1 == row2) {
        int min = std::min(column1, column2);
        int max = std::max(column1, column2);
        if (max - min <= 1 || board[row1][max] != board[row2][min]) {
            return false;
        }
        int color = board[row1][max];
        for (int i = min + 1; i < max; i++) {
            if (board[row1][i] != -color) {
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
            if (board[i][column1] != -color) {
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
        int color = board[max][sum - max];
        for (int i = min + 1; i < max; i++) {
            if (board[i][sum - i] != -color) {
                return false;
            }
        }
        return true;
    }

    if (row1 - column1 == row2 - column2) {
        int diff = row1 - column1;
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);
        if (max - min <= 1 || board[min][min - diff] != board[max][max - diff]) {
            return false;
        }
        int color = board[max][max - diff];
        for (int i = min + 1; i < max; i++) {
            if (board[i][i - diff] != -color) {
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
            board[row1][i] = color;
        }
        return;
    }

    if (column1 == column2) {
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);

        int color = board[max][column1];
        for (int i = min + 1; i < max; i++) {
            board[i][column1] = color;
        }
        return;
    }

    if (row1 + column1 == row2 + column2) {
        int sum = row1 + column1;
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);

        int color = board[max][sum - max];
        for (int i = min + 1; i < max; i++) {
            board[i][sum - i] = color;
        }
        return;
    }

    if (row1 - column1 == row2 - column2) {
        int diff = row1 - column1;
        int min = std::min(row1, row2);
        int max = std::max(row1, row2);

        int color = board[max][max - diff];
//        std::cerr << "color:" << color << std::endl;
        for (int i = min + 1; i < max; i++) {
            board[i][i - diff] = color;
        }
        return;
    }
}

std::vector<std::pair<int, int>> Reversi::possibleMovement(int color) {
    std::vector<std::pair<int, int>> ret;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isValid(i, j, color)) {
                ret.emplace_back(i, j);
            }
        }
    }
    return ret;
}

Reversi::Reversi(const Reversi &reversi) {
    this->board = reversi.board;
}

bool Reversi::isTerminal() {
    int flag = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 0) {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0) {
        return true;
    } else {
        return possibleMovement(WHITE).size() == 0 && possibleMovement(BLACK).size() == 0;
    }

}

bool Reversi::isWin(int color) {
    if (isTerminal()) {
        int white = 0;
        int black = 0;
        for (auto row : board) {
            for (auto column : row) {
                if (column == WHITE) {
                    white++;
                } else if (column == BLACK) {
                    black++;
                }
            }
        }
        return (white > black && color == WHITE) || (white < black && color == BLACK);
    }
    assert(false);
}

void Reversi::printBoard() {
    printf("   ");
    for (int k = 0; k < 8; ++k) {
        printf("%3d", k);
    }
    std::cout << std::endl;

    printf("-------------------------------------\n");
    int index = 0;
    for (auto i : board) {
        printf("%2d|", index);
        index++;
        for (auto j : i) {

            printf("%3d", j);
        }
        std::cout << std::endl;
    }
}

void Reversi::setBoard(const std::array<std::array<int, 8>, 8> &board) {
    Reversi::board = board;
}




