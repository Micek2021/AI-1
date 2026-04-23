//
// Created by mikol on 23.04.2026.
//

#ifndef AGENT_H
#define AGENT_H
#include "board.h"
#include "evaluator.h"
#include "move.h"


class Agent {
public:
    Move getBestMove(Board& board, player p, const Evaluator& evaluator, int depth);

    [[nodiscard]] int getNodesVisited() const;
    void resetNodesVisited();
private:
    int nodesVisited = 0;

    int minimax(Board& board, player p, player maximising, const Evaluator& evaluator, int depth);

    int alphabeta(Board& board, player p, player maximising, const Evaluator& evaluator, int depth, int alpha = INT_MIN, int beta = INT_MAX);
};



#endif //AGENT_H
