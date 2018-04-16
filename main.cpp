#include <iostream>
#include "Reversi.h"
#include <cstdio>

int main() {
    std::cout << "Hello, World!" << std::endl;
    Reversi r = Reversi();
    while (true) {
        int row = 0, column = 0, color = 0;
        std::cin >> row >> column >> color;
        r.next(row, column, color);
        for(auto i : r.getBoard()){
            for(auto j : i){
                printf("%3d", j);
            }
            std::cout << std::endl;
        }
//        break;
    }
    return 0;
}