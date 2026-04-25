//
// Created by mikol on 25.04.2026.
//

#include "test_game.h"
#include "agent.h"
#include <iostream>
#include <chrono>

game_state runGame(Evaluator& whitePlayer, Evaluator& blackPlayer, int depth, bool verbose) {
    /* SINGLE DUEL */

    Board board;
    Agent agent;
    int rounds = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (board.getGameState() == ongoing) {
        Move white = agent.getBestMove(board, white_player, whitePlayer, depth);
        board.makeMove(white);
        rounds++;
        if (verbose) std::cout << board << std::endl;
        if (board.getGameState() != ongoing) break;

        Move black = agent.getBestMove(board, black_player, blackPlayer, depth);
        board.makeMove(black);
        rounds++;
        if (verbose) std::cout << board << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    if (verbose){
    std::cout << "----------------GAME OVER----------------" << std::endl;
    std::cout << board << std::endl;
    std::cout << "Rounds: " << rounds << std::endl;
    std::cout << (board.getGameState() == white_won ? "White player won" : "Black player won") << std::endl;

    std::cerr << "Visited nodes: " << agent.getNodesVisited() << std::endl;
    std::cerr << "Time: " << duration.count() << " seconds" << std::endl;
    }

    return board.getGameState();
}