//
// Created by mikol on 23.04.2026.
//

#include "evaluator.h"

#include <algorithm>
#include <utility>

Evaluator::Evaluator(std::vector<int> weights, bool preferCentre) : weights(std::move(weights)), preferCentre(preferCentre){}

int Evaluator::evaluate(const Board &board, player p) const {
    const auto& stateBoard = board.getBoard();
    const int rows = board.getRows();
    const int cols = board.getCols();
    const cell friendly = p == white_player ? white : black;
    const cell enemy = p == white_player ? black : white;

    const double centerCol = (cols - 1) / 2.0;

    int countPawns = 0;
    int mostAdvanced = 0;
    int zoneControl = 0;
    int coverage = 0;
    std::vector<int> positions;


    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (stateBoard[row][col] == friendly) {
                ++countPawns;

                int adv = p == white_player ? row : (rows - 1 - row);
                positions.push_back(adv);
                if (adv > mostAdvanced) mostAdvanced = adv;

                if (preferCentre) {
                    if (col >= centerCol - 2 && col <= centerCol + 2) zoneControl++;
                } else {
                    if (col < centerCol - 2 || col > centerCol + 2) zoneControl++;
                }

                if (col < cols - 1 && stateBoard[row][col + 1] == friendly) {
                    coverage++;
                }
            } else if (stateBoard[row][col] == enemy) {
                countPawns--;
            }
        }
    }

    int medianAdv = 0;
    if (!positions.empty()) {
        std::ranges::sort(positions);
        medianAdv = positions[positions.size() / 2];
    }

    return weights[0] * countPawns
        + weights[1] * (medianAdv * 2)
        + weights[2] * mostAdvanced
        + weights[3] * zoneControl
        + weights[4] * coverage;
}

