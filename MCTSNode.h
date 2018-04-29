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
    int wonTimes = 0;
    int visitTimes = 0;
    bool win = false;
    MCTSNode *father;

public:
    int color;

    Reversi boardState;

    std::vector<std::shared_ptr<MCTSNode>> children;

    MCTSNode(MCTSNode *father, const Reversi &boardState, int color);

    bool isAllExpanded();

    std::shared_ptr<MCTSNode> bestChild();

    std::shared_ptr<MCTSNode> randomUnexpandedChild();

    void genChildren();
    void setNullFather();

    friend std::shared_ptr<MCTSNode> selection(std::shared_ptr<MCTSNode> node);

    friend std::shared_ptr<MCTSNode> expansion(std::shared_ptr<MCTSNode> node);

    friend std::shared_ptr<MCTSNode> simulation(std::shared_ptr<MCTSNode> node);

    friend void backpropagation(MCTSNode *node, int color);


    std::shared_ptr<MCTSNode> completeGameRandomly();

    static const int C = static_cast<const int>(sqrt(2));

    std::shared_ptr<MCTSNode> decideNext();

    std::shared_ptr<MCTSNode> selectNext(int row, int column);

    std::shared_ptr<MCTSNode> genChild(int row, int column);
};


#endif //REVERSI_MCTSNODE_H
