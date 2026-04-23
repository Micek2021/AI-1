//
// Created by mikol on 23.04.2026.
//

#include "agent.h"


int Agent::minimax(Board &board, player p, player maximising, const Evaluator &evaluator, int depth) {
    nodesVisited++;

    if (depth == 0 || board.getGameState() != ongoing) {
        game_state gs = board.getGameState();
        if (gs == white_won) return maximising == white_player ? 10000000 : -10000000;
        if (gs == black_won) return maximising == black_player ? 10000000 : -10000000;
        return evaluator.evaluate(board, maximising);
    }

    auto moves = board.getLegalMoves(p);

    if (p == maximising) {
        int best = INT_MIN;
        for (auto move : moves) {
            board.makeMove(move);
            int value = minimax(board, p == white_player ? black_player : white_player, maximising, evaluator, depth - 1);
            board.undoMove(move);
            if (value > best) best = value;
        }
        return best;
    } else {
        int best = INT_MAX;
        for (auto move : moves) {
            board.makeMove(move);
            int value = minimax(board, p == white_player ? black_player : white_player, maximising, evaluator, depth - 1);
            board.undoMove(move);
            if (value < best) best = value;
        }
        return best;
    }
}

int Agent::alphabeta(Board &board, player p, player maximising, const Evaluator &evaluator, int depth, int alpha, int beta) {
    nodesVisited++;

    if (depth == 0 || board.getGameState() != ongoing) {
        game_state gs = board.getGameState();
        if (gs == white_won) return maximising == white_player ? 10000000 : -10000000;
        if (gs == black_won) return maximising == black_player ? 10000000 : -10000000;
        return evaluator.evaluate(board, maximising);
    }

    auto moves = board.getLegalMoves(p);

    if (p == maximising) {
        for (auto move : moves) {
            board.makeMove(move);
            int value = alphabeta(board, p == white_player ? black_player : white_player, maximising, evaluator, depth - 1, alpha, beta);
            board.undoMove(move);
            if (value > alpha) alpha = value;
            if (beta <= alpha) break;
        }
        return alpha;
    } else {
        for (auto move : moves) {
            board.makeMove(move);
            int value = alphabeta(board, p == white_player ? black_player : white_player, maximising, evaluator, depth - 1, alpha, beta);
            board.undoMove(move);
            if (value < beta) beta = value;
            if (beta <= alpha) break;
        }
        return beta;
    }
}


Move Agent::getBestMove(Board &board, player p, const Evaluator &evaluator, int depth) {
    auto moves = board.getLegalMoves(p);
    Move bestMove = moves[0];
    int bestValue = INT_MIN;

    for (auto move : moves) {
        board.makeMove(move);
        int value = minimax(board, p == white_player ? black_player : white_player, p, evaluator, depth - 1);
        board.undoMove(move);
        if (value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }
    return bestMove;
}

int Agent::getNodesVisited() const {
    return nodesVisited;
}

void Agent::resetNodesVisited() {
    nodesVisited = 0;
}

