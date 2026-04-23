//
// Created by mikol on 23.04.2026.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "board.h"


class Evaluator {
    std::vector<int> weights;
    bool preferCentre;
public:
    explicit Evaluator(std::vector<int> weights, bool preferCentre);

    [[nodiscard]] int evaluate(const Board& board, player p) const;
};



#endif //EVALUATOR_H
