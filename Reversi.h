//
// Created by DFZ on 2018/4/12.
//

#ifndef REVERSI_REVERSI_H
#define REVERSI_REVERSI_H


#include <array>
#include <vector>
#include <memory>

#define BLACK -1
#define WHITE 1

class Reversi {
private:
    std::array<std::array<int, 8>, 8> board;

public:
    void setBoard(const std::array<std::array<int, 8>, 8> &board);

    Reversi();

    Reversi(const Reversi &reversi);

    Reversi next(int row, int column, int color);

    std::array<std::array<int, 8>, 8> getBoard();

    bool isValid(int row, int column, int color);

    bool canFlip(int row1, int column1, int row2, int column2);

    void flip(int row1, int column1, int row2, int column2);

    std::vector<std::pair<int, int>> possibleMovement(int color);

    bool isTerminal();

    bool isWin(int color);

    void printBoard();
};


#endif //REVERSI_REVERSI_H
