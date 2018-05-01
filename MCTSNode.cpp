//
// Created by DFZ on 2018/4/18.
//

#include <cassert>
#include <iostream>
#include "MCTSNode.h"

MCTSNode::MCTSNode(MCTSNode *father, const Reversi &boardState, int color) : father(father), boardState(boardState),
                                                                             color(color) {}

bool MCTSNode::isAllExpanded() {
//    return children.size()==boardState.possibleMovement(color).size();
    if (children.size() == 0) {
        return false;
    }

    for (auto child : children) {
        if (child->visitTimes == 0) { return false; }
    }
    return true;

}

std::shared_ptr<MCTSNode> MCTSNode::bestChild() {
    double max = -1;
    std::shared_ptr<MCTSNode> bestChild;
    for (auto child  : children) {
        if (child->visitTimes == 0) {
            continue;
        }
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

std::shared_ptr<MCTSNode> MCTSNode::randomUnexpandedChild() {

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
        auto child = std::make_shared<MCTSNode>(this, this->boardState.next(step.first, step.second, color), -color);
//        children.push_back(child);
        children.emplace_back(child);
    }
}


std::shared_ptr<MCTSNode> selection(std::shared_ptr<MCTSNode> node) {
    while (node->children.size() != 0) {
        if (node->isAllExpanded()) {
            return selection(node->bestChild());
        } else {
            return selection(node->randomUnexpandedChild());
        }
    }
    return node;
}


std::shared_ptr<MCTSNode> expansion(std::shared_ptr<MCTSNode> node) {
    if (node->boardState.isTerminal()) {
        return node;
    } else {
        node->genChildren();
        return node->randomUnexpandedChild();
    }
}

std::shared_ptr<MCTSNode> simulation(std::shared_ptr<MCTSNode> node) {
    if (node->boardState.isTerminal()) { return node; }
    else {
        return node->completeGameRandomly();
    }

}

void backpropagation(MCTSNode *node, int color) {
    //    node->win = node->boardState.isWin(color);
    node->win = node->boardState.isWin(color);
    bool win = node->win;
    node->visitTimes++;
    if (win) {
        node->wonTimes++;
    }
    while (node->father != nullptr) {
        node->father->visitTimes++;
        if (win) {
            node->father->wonTimes++;
        }
        node = node->father;
    }
//    std::cout << "back complete" << std::endl;
}

std::shared_ptr<MCTSNode> MCTSNode::completeGameRandomly() {
//    return nullptr;
    auto node = this;
    std::shared_ptr<MCTSNode> retChild;
    while (!node->boardState.isTerminal()) {
        auto possibleMove = node->boardState.possibleMovement(node->color);

//        std::cout << "possibleMove size: " << possibleMove.size() << std::endl;

        if (possibleMove.size() == 0) {
//            std::cout << "no possible movement, next player go" << std::endl;
            auto child = std::make_shared<MCTSNode>(node, node->boardState, -node->color);
            node->children.push_back(child);
            node = child.get();
            retChild = child;
            continue;
        }

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<size_t> uniform_dist(0, possibleMove.size() - 1);
        size_t mean = uniform_dist(e1);
//        std::cout << "movement: " << possibleMove[mean].first << " " << possibleMove[mean].second << " " << node->color
//                  << std::endl;
        auto board = node->boardState.next(possibleMove[mean].first, possibleMove[mean].second, node->color);
//        board.printBoard();

        auto child = std::make_shared<MCTSNode>(node, board, -node->color);
        node->children.push_back(child);
        node = child.get();
        retChild = child;
    }
    return retChild;
}

std::shared_ptr<MCTSNode> MCTSNode::decideNext() {
    double max = -1;
    std::shared_ptr<MCTSNode> bestChild = nullptr;
    for (auto child  : children) {
        if (child->visitTimes == 0) {
            continue;
        }
        double childUCB =
                child->wonTimes / child->visitTimes + MCTSNode::C * sqrt(log(this->visitTimes / child->visitTimes));
        if (childUCB > max) {
            max = childUCB;
            bestChild = child;
        }
    }
    std::cout << "UCB: " << max << std::endl;
    std::cout << "children size: " << children.size() << std::endl;
    for (auto child : children) {
        std::cout << "won times:" << child->wonTimes << " visit times: " << child->visitTimes << std::endl;
    }

    assert(bestChild);

    bestChild->father = nullptr;
    return bestChild;
}

std::shared_ptr<MCTSNode> MCTSNode::selectNext(int row, int column) {
    if (this->children.size() == 0) {
        genChildren();
    }
    for (auto child : children) {
        if (child->boardState.getBoard()[row][column] == color) {
            child->father = nullptr;
            return child;
        }
    }
    auto child = genChild(row, column);
    std::cout << "I gen a child" << std::endl;
    child->father = nullptr;
    return child;
//            assert(false);
//    return nullptr;
}


std::shared_ptr<MCTSNode> MCTSNode::genChild(int row, int column) {
    auto child = std::make_shared<MCTSNode>(this, this->boardState.next(row, column, color), -color);
    children.push_back(child);
    return child;
}
