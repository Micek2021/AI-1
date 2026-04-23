//
// Created by mikol on 01.04.2026.
//

#ifndef BOARD_H
#define BOARD_H
#include <ostream>
#include <vector>
#include "move.h"


enum player {
    white_player,
    black_player
};

enum game_state {
    ongoing,
    white_won,
    black_won
};

std::string to_string(game_state state);

class Board {
    int rows;
    int cols;
    std::vector<std::vector<cell>> board;

public:
    Board();

    Board(int rows, int cols);

    [[nodiscard]] std::vector<Move> getLegalMoves(player playerColour) const;

    void makeMove(const Move &move);

    void undoMove(const Move &move);

    [[nodiscard]] game_state getGameState() const;

    [[nodiscard]] cell getCell(int x, int y) const;

    void startOrReset();

    [[nodiscard]] std::string toString() const;

    //gettery
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
    [[nodiscard]] const std::vector<std::vector<cell>>& getBoard() const;

private:
    [[nodiscard]] std::vector<Move> getPossibleMovesForSinglePawn(int col, int row, player playerColour) const;

};

std::ostream &operator<<(std::ostream &os, const Board &board);



#endif //BOARD_H
