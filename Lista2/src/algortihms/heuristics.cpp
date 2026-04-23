//
// Created by mikol on 21.04.2026.
//

#include "heuristics.h"

int CountPawns::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = p == white_player ? white : black;
    const cell enemy = p == white_player ? black : white;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (stateBoard[row][col] == friendly) {
                result += 1;
            } else if (stateBoard[row][col] == enemy) {
                result -= 1;
            }
        }
    }

    return result;
}

int Advancement::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = p == white_player ? white : black;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (stateBoard[row][col] == friendly) {
                result += p == white_player ? row : (rows - 1 - row);
            }
        }
    }

    return result;
}

int MostAdvanced::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = p == white_player ? white : black;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (stateBoard[row][col] == friendly) {
                int advancement = p == white_player ? row : (rows - 1 - row);
                if (advancement > result) result = advancement;
            }
        }
    }

    return result;
}

int CentreControl::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = p == white_player ? white : black;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    double centerCol = (cols - 1) / 2.0;
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            if (stateBoard[row][col] == friendly) {
                result += static_cast<int>(centerCol - std::abs(col - centerCol));
            }
        }
    }

    return result;
}

int SideControl::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = p == white_player ? white : black;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    const double centerCol = (cols - 1) / 2.0;
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            if (stateBoard[row][col] == friendly) {
                result += static_cast<int>(std::abs(centerCol - col));
            }
        }
    }

    return result;
}


int Coverage::evaluate(const Board &board, player p) const {
    const cell friendly = p == white_player ? white : black;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    std::vector<bool> colHasPawn(cols, false);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (stateBoard[row][col] == friendly) {
                colHasPawn[col] = true;
            }
        }
    }

    int covered = 0;
    for (int col = 0; col < cols; ++col) {
        if (colHasPawn[col]) covered++;
    }
    return covered;
}


int GuaranteedWin::evaluate(const Board &board, player p) const {
    const cell friendly = p == white_player ? white : black;
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();

    const int preWinRow = p == white_player ? rows - 2 : 1;

    for (int col = 0; col < cols; ++col) {
        if (stateBoard[preWinRow][col] == friendly) {
            return 1000000;
        }
    }
    return 0;
}