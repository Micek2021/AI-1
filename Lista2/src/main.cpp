#include "board.h"
#include "evaluator.h"
#include "agent.h"
#include "test_benchmark.h"
#include "test_game.h"
#include "test_tournament.h"
#include "test_genetic.h"

int main() {
    int depth = 2;

    std::vector<NamedEvaluator> competitors = {
        {"FluidAggSides",       Evaluator({8, 17, 18, 6, 4}, false)},
        {"FluidAggCenter",      Evaluator({16, 17, 12, 4, 5}, true)},
        {"StructBalSides",      Evaluator({20, 9, 4, 17, 13}, false)},
        {"StructBalCenter",     Evaluator({16, 10, 5, 17, 13}, true)},
        {"StructCovSides",      Evaluator({20, 5, 4, 17, 20}, false)},
        {"StructCovCenter",     Evaluator({16, 5, 4, 17, 16}, true)}
    };

    runTournament(competitors, depth);

    Evaluator FluidAggSides({8, 17, 18, 6, 4}, false);
    Evaluator FluidAggCenter({16, 17, 12, 4, 5}, true);

    runGame(FluidAggCenter, FluidAggSides, depth);

    runBenchmark(depth);

    runGenetic(50, 30, 2);

    return 0;
}