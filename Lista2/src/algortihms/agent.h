//
// Created by mikol on 23.04.2026.
//

#ifndef AGENT_H
#define AGENT_H

#include "board.h"
#include "evaluator.h"
#include "move.h"


class Agent {
    int nodesVisited = 0;

public:
    Move getBestMove(Board& board, player p, const Evaluator& evaluator, int depth, bool useAlphaBeta = true);

    [[nodiscard]] int getNodesVisited() const;
    void resetNodesVisited();

private:
    int miniMax(Board& board, player p, player maximising, const Evaluator& evaluator, int depth);

    int alphaBeta(Board& board, player p, player maximising, const Evaluator& evaluator, int depth, int alpha = INT_MIN, int beta = INT_MAX);
};



#endif //AGENT_H
