//
// Created by DFZ on 2018/4/18.
//

#ifndef REVERSI_MCTSNODE_H
#define REVERSI_MCTSNODE_H

#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include "Reversi.h"

class MCTSNode {
private:
    int color;
    int wonTimes = 0;
    int visitTimes = 0;
    bool win = false;
    MCTSNode *father;
    Reversi boardState;

public:
    std::vector<MCTSNode *> children;

    MCTSNode(MCTSNode *father, const Reversi &boardState, int color);

    bool isAllExpanded();

    MCTSNode *bestChild();

    MCTSNode *randomUnexpandedChild();

    void genChildren();

    friend MCTSNode *expasion(MCTSNode *node);

    friend MCTSNode *simulatoin(MCTSNode *node);

    friend void backpropagation(MCTSNode *node);


    MCTSNode *completeGameRandomly();

    static const int C = static_cast<const int>(sqrt(2));
};


#endif //REVERSI_MCTSNODE_H
