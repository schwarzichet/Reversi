#include <iostream>

#include "Reversi.h"
#include "MCTSNode.h"
#include <cstdio>


int main() {
    std::cout << "Hello!" << std::endl;
    Reversi r = Reversi();
    r.printBoard();
    auto root = std::make_shared<MCTSNode>(nullptr, r, BLACK);
    while (!root->boardState.isTerminal()) {

        int row = 0, column = 0;
        std::cin >> row >> column;
//        Reversi newBoard = root->boardState.next(row, column, root->color);
//        root = new MCTSNode(nullptr, newBoard, -root->color);
        root = root->selectNext(row, column);


        auto leaf  = selection(root);
        auto newChild = expansion(leaf);
        auto result = simulation(newChild);
        backpropagation(result.get());
        root = root->decideNext();
//        r = r.next(row, column, color);
//        r.printBoard();
//        root = new MCTSNode(nullptr, r, )
    }
    return 0;
}
