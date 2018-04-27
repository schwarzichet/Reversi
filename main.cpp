#include <iostream>
#include "Reversi.h"
#include "MCTSNode.h"
#include <cstdio>


int main() {
    std::cout << "Hello!" << std::endl;
    Reversi r = Reversi();
    r.printBoard();
    while (!r.isTerminal()) {
        int row = 0, column = 0, color = 0;
        std::cin >> row >> column >> color;
        r = r.next(row, column, color);
        r.printBoard();

    }
    return 0;
}
