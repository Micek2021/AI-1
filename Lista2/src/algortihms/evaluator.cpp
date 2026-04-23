//
// Created by mikol on 23.04.2026.
//

#include "evaluator.h"

#include <utility>

Evaluator::Evaluator(std::vector<int> weights, bool preferCentre) : weights(std::move(weights)), preferCentre(preferCentre){}

int Evaluator::evaluate(const Board &board, player p) const {
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();
    const cell friendly = p == white_player ? white : black;

    const double centerCol = (cols - 1) / 2.0;
    const cell enemy = p == white_player ? black : white;

    int countPawns = 0;
    int advancement = 0;
    int mostAdvanced = 0;
    int colControl = 0;
    std::vector colHasPawn(cols, false);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (stateBoard[row][col] == friendly) {
                ++countPawns;
                int adv = p == white_player ? row : (rows - 1 - row);
                advancement += adv;
                if (adv > mostAdvanced) mostAdvanced = adv;
                int colScore = preferCentre
                                   ? static_cast<int>(centerCol - std::abs(col - centerCol))
                                   : static_cast<int>(std::abs(col - centerCol));
                colControl += colScore;
                colHasPawn[col] = true;
            } else if (stateBoard[row][col] == enemy) {
                countPawns--;
            }
        }
    }

    int coverage = 0;
    for (int col = 0; col < cols; ++col) {
        if (colHasPawn[col]) ++coverage;
    }

    return weights[0] * countPawns
           + weights[1] * advancement
           + weights[2] * mostAdvanced
           + weights[3] * colControl
           + weights[4] * coverage
            ;
}
