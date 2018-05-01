#include <iostream>

#include "Reversi.h"
#include "MCTSNode.h"
#include "server.hpp"

#define SERVER

#undef SERVER

#ifndef SERVER

int main() {
    std::cout << "Hello!" << std::endl;
    std::cout << "which side do you want to play? 1 for white;-1 for black" << std::endl;
    int playerColor;
    std::cin >> playerColor;
    Reversi r = Reversi();
    auto root = std::make_shared<MCTSNode>(nullptr, r, BLACK);

    if (playerColor == WHITE) {
        auto leaf = selection(root);
        std::cerr << "[debug]selection ok" << std::endl;
        auto newChild = expansion(leaf);
        std::cerr << "[debug]expansion ok" << std::endl;

        auto result = simulation(newChild);
        std::cerr << "[debug]simulation ok" << std::endl;

        backpropagation(result.get(), root->color);
        std::cerr << "[debug]backpropagation ok" << std::endl;

        root = root->decideNext();
    } else if (playerColor == BLACK) {
    } else {
        std::cout << "wrong color." << std::endl;
        return 1;
    }

    root->boardState.printBoard();

    while (!root->boardState.isTerminal()) {
        int row = 0, column = 0;
        std::cin >> row >> column;
        while (!root->boardState.isValid(row, column, root->color)) {
            std::cout << "invalid movement!" << std::endl;
            std::cin >> row >> column;
        }
        root = root->selectNext(row, column);
        root->boardState.printBoard();
        for (int j = 0; j < 1000; ++j) {
            //        while (!root->isAllExpanded()){
            auto leaf = selection(root);
//            std::cerr << "[debug]selection ok" << std::endl;
            auto newChild = expansion(leaf);
//            std::cerr << "[debug]expansion ok" << std::endl;
            for (int i = 0; i < 10; ++i) {
                auto result = simulation(newChild);
//                std::cerr << "[debug]simulation ok" << std::endl;
                backpropagation(result.get(), root->color);
//                std::cerr << "[debug]backpropagation ok" << std::endl;
            }
//            std::cerr << "[debug]simulation ok" << std::endl;
//            std::cerr << "[debug]backpropagation ok" << std::endl;
//        }
        }


        root = root->decideNext();
        root->boardState.printBoard();
    }

    if (root->boardState.isWin(BLACK)) {
        std::cout << "BLACK win" << std::endl;
    } else {
        std::cout << "WHITE win" << std::endl;
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
