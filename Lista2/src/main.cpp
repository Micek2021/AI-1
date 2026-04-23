#include <iostream>
#include <chrono>
#include "board/board.h"
#include "algortihms/evaluator.h"
#include "algortihms/Agent.h"

int main() {
    std::ios::sync_with_stdio(true);
    Board board;
    Evaluator evaluator({3, 2, 3, 1, 1}, true);
    Agent agent;
    int depth = 3;
    int rounds = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (board.getGameState() == ongoing) {
        Move white = agent.getBestMove(board, white_player, evaluator, depth);
        board.makeMove(white);
        rounds++;
        std::cout << board << std::endl;
        if (board.getGameState() != ongoing) break;

        Move black = agent.getBestMove(board, black_player, evaluator, depth);
        board.makeMove(black);
        rounds++;
        std::cout << board << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "----------------KONIEC GRY----------------" << std::endl;
    std::cout << board << std::endl;
    std::cout << "Rundy: " << rounds << std::endl;
    std::cout << (board.getGameState() == white_won ? "Wygral bialy" : "Wygral czarny") << std::endl;

    std::cerr << "Odwiedzone wezly: " << agent.getNodesVisited() << std::endl;
    std::cerr << "Czas: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
