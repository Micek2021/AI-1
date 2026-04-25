//
// Created by mikol on 25.04.2026.
//

#ifndef BREAKTHROUGH_TEST_TOURNAMENT_H
#define BREAKTHROUGH_TEST_TOURNAMENT_H

#include "evaluator.h"

struct NamedEvaluator {
    std::string name;
    Evaluator eval;
};

void runTournament(std::vector<NamedEvaluator>& competitors, int depth);


#endif //BREAKTHROUGH_TEST_TOURNAMENT_H
