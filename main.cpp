#include <iostream>

#include "Reversi.h"
#include "MCTSNode.h"
#include <cstdio>


int main() {
    std::cout << "Hello!" << std::endl;
    Reversi r = Reversi();
//    std::array<std::array<int, 8>, 8> a;
//    a[0] = {-1, 1, 1, 1, 1, 1, -1, -1};
//    a[1] = {0, 1, -1, 1, 1, 1, 1 - 1, 0};
//    a[2] = {-1, 1, 1, -1, -1, -1, -1, -1};
//    a[3] = {0, -1, 1, 1, -1, -1, -1, -1};
//    a[4] = {-1, 1, -1, -1, 1, -1, -1, -1};
//    a[5] = {1, 1, 1, -1, -1, 1, -1, -1};
//    a[6] = {0, 1, 1, 1, -1, -1, 1, -1};
//    a[7] = {-1, -1, -1, -1, -1, -1, -1, 1};
//    r.setBoard(a);
//    r.printBoard();
//    r.next(1, 0, -1).printBoard();

    r.printBoard();
    auto root = std::make_shared<MCTSNode>(nullptr, r, BLACK);
    while (!root->boardState.isTerminal()) {

        int row = 0, column = 0;
        std::cin >> row >> column;
//        Reversi newBoard = root->boardState.next(row, column, root->color);
//        root = new MCTSNode(nullptr, newBoard, -root->color);


        while (!root->boardState.isValid(row, column, root->color)) {
            std::cout << "invalid movement!" << std::endl;
            std::cin >> row >> column;
        }
        root = root->selectNext(row, column);


        root->boardState.printBoard();

        auto leaf = selection(root);
        std::cerr << "[debug]selection ok" << std::endl;
        auto newChild = expansion(leaf);
        std::cerr << "[debug]expansion ok" << std::endl;

        auto result = simulation(newChild);
        std::cerr << "[debug]simulation ok" << std::endl;

        backpropagation(result.get(), root->color);
        std::cerr << "[debug]backpropagation ok" << std::endl;

        root = root->decideNext();
//        root->setNullFather();
        root->boardState.printBoard();
//        r = r.next(row, column, color);
//        r.printBoard();
//        root = new MCTSNode(nullptr, r, )
    }
    return 0;
}
