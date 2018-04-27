//
// Created by DFZ on 2018/4/18.
//

#include <cassert>
#include "MCTSNode.h"

MCTSNode::MCTSNode(MCTSNode *father, const Reversi &boardState, int color) : father(father), boardState(boardState),
                                                                             color(color) {}

bool MCTSNode::isAllExpanded() {
//    return children.size()==boardState.possibleMovement(color).size();
    for (auto child : children) {
        if (child->visitTimes == 0) { return false; }
    }
    return true;

}

MCTSNode *MCTSNode::bestChild() {
    double max = 0;
    MCTSNode *bestChild = nullptr;
    for (auto child  : children) {
        double childUCB =
                child->wonTimes / child->visitTimes + MCTSNode::C * sqrt(log(this->visitTimes / child->visitTimes));
        if (childUCB > max) {
            max = childUCB;
            bestChild = child;
        }
    }
    assert(bestChild != nullptr);
    return bestChild;
}

MCTSNode *MCTSNode::randomUnexpandedChild() {
    std::random_device r;
    size_t mean;
    do {
        std::default_random_engine e1(r());
        std::uniform_int_distribution<size_t> uniform_dist(0, children.size() - 1);
        mean = uniform_dist(e1);
    } while (children[mean]->visitTimes != 0);
    return children[mean];

}

void MCTSNode::genChildren() {
    for (auto step : this->boardState.possibleMovement(color)) {
        MCTSNode *child = new MCTSNode(this, this->boardState.next(step.first, step.second, color), -color);
        children.push_back(child);
    }
    //TODO: need delete.....
}


MCTSNode *selection(MCTSNode *node) {
    while (node->children.size() == 0) {
        if (node->isAllExpanded()) {
            return selection(node->bestChild());
        } else {
            return selection(node->randomUnexpandedChild());
        }
    }
}


MCTSNode *expasion(MCTSNode *node) {
    if (node->boardState.isTerminal()) {
        return node;
    } else {
        node->genChildren();
        return node->randomUnexpandedChild();
    }
}

MCTSNode *simulatoin(MCTSNode *node) {
    if (node->boardState.isTerminal()) { return node; }
    else {
        return node->completeGameRandomly();
    }

}

void backpropagation(MCTSNode *node) {
    bool win = node->win;
    while (node->father == nullptr) {
        node->father->visitTimes++;
        if (win) {
            node->father->wonTimes++;
        }
    }
}

MCTSNode *MCTSNode::completeGameRandomly() {
//    return nullptr;
    MCTSNode *node = this;
    while (!node->boardState.isTerminal()) {
        auto possibleMove = node->boardState.possibleMovement(node->color);
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<size_t> uniform_dist(0, possibleMove.size() - 1);
        size_t mean = uniform_dist(e1);
        auto board = node->boardState.next(possibleMove[mean].first, possibleMove[mean].second, color);
        node = new MCTSNode(node, board, -color);
    }
    node->boardState.setWin();

    return node;
}


