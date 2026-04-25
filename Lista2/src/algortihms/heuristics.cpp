//
// Created by mikol on 21.04.2026.
//

#include "heuristics.h"
#include <algorithm>

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
    std::vector<int> positions;
    const cell friendly = (p == white_player) ? white : black;

    for (int r = 0; r < board.getRows(); ++r) {
        for (int c = 0; c < board.getCols(); ++c) {
            if (board.getCell(r, c) == friendly) {
                positions.push_back(p == white_player ? r : (board.getRows() - 1 - r));
            }
        }
    }
    if (positions.empty()) return 0;
    std::ranges::sort(positions);

    return positions[positions.size() / 2] * 2;
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

    return std::max(0, result - 1);
}

int CentreControl::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = (p == white_player) ? white : black;
    int cols = board.getCols();
    int mid = cols / 2;

    for (int r = 0; r < board.getRows(); ++r) {
        for (int c = mid - 2; c <= mid + 1; ++c) {
            if (board.getCell(r, c) == friendly) result++;
        }
    }
    return result;
}

int SideControl::evaluate(const Board &board, player p) const {
    int result = 0;
    const cell friendly = p == white_player ? white : black;
    const int cols = board.getCols();
    const int rows = board.getRows();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (col <= 1 || col >= cols - 2) {
                if (board.getCell(row, col) == friendly) {
                    result++;
                }
            }
        }
    }

    return result;
}

int Coverage::evaluate(const Board &board, player p) const {
    int pairs = 0;
    const cell friendly = (p == white_player) ? white : black;

    for (int r = 0; r < board.getRows(); ++r) {
        for (int c = 0; c < board.getCols() - 1; ++c) {
            if (board.getCell(r, c) == friendly && board.getCell(r, c + 1) == friendly) {
                pairs++;
            }
        }
    }
    return pairs;
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