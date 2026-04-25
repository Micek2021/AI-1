//
// Created by mikol on 25.04.2026.
//

#include "test_benchmark.h"
#include "agent.h"
#include <iostream>
#include <chrono>

void runBenchmark(int maxDepth) {
    /* ALPHA BETA VS MINIMAX TESTS*/

    Board board;
    Agent agent;
    Evaluator eval({16, 17, 12, 4, 5}, true);
    for (int d = 2; d <= 5; ++d) {
        // Minimax
        agent.resetNodesVisited();
        auto s1 = std::chrono::high_resolution_clock::now();
        agent.getBestMove(board, white_player, eval, d, false);
        auto e1 = std::chrono::high_resolution_clock::now();
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(e1 - s1).count();
        std::cerr << d << " MM " << agent.getNodesVisited() << " " << t1 << "ms" << std::endl;

        // Alpha-Beta
        agent.resetNodesVisited();
        auto s2 = std::chrono::high_resolution_clock::now();
        agent.getBestMove(board, white_player, eval, d, true);
        auto e2 = std::chrono::high_resolution_clock::now();
        auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(e2 - s2).count();
        std::cerr << d << " AB " << agent.getNodesVisited() << " " << t2 << "ms" << std::endl;
    }
}