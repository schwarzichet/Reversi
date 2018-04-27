#include <iostream>
#include <cstdio>

#include "Reversi.h"
#include "MCTSNode.h"
#include "server.hpp"

#define SERVER

#undef SERVER

#ifndef SERVER

int main() {
    std::cout << "Hello!" << std::endl;
    Reversi r = Reversi();
    r.printBoard();
    MCTSNode* root;
    while (!r.isTerminal()) {
        int row = 0, column = 0, color = 0;
        std::cin >> row >> column >> color;
        r = r.next(row, column, color);
        r.printBoard();
//        root = new MCTSNode(nullptr, r, )
    }
    return 0;
}

#endif // ifndef SERVER

#ifdef SERVER

int main(const int agrc, const char *argv[])
{
    server();
    return 0;
}

#endif // ifndef SERVER
