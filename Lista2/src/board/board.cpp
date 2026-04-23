//
// Created by mikol on 01.04.2026.
//

#include "board.h"

Board::Board() : rows(8), cols(8) {
    startOrReset();
}


Board::Board(int rows, int cols) : rows(rows), cols(cols) {
    startOrReset();
}

void Board::startOrReset() {
    board.assign(rows, std::vector<cell>(cols, empty));

    for (int col = 0; col < cols; col++) {
        board[0][col] = white;
        board[1][col] = white;
        board[rows - 1][col] = black;
        board[rows - 2][col] = black;
    }
}


std::vector<Move> Board::getPossibleMovesForSinglePawn(int col, int row, player playerColour) const {
    std::vector<Move> possibleMoves;

    const int dir = (playerColour == white_player ? 1 : -1);
    cell enemyPawns = playerColour == white_player ? black : white;
    const int rowPos = row + dir;


    if (rowPos < 0 || rowPos >= rows) {
        return possibleMoves;
    }

    for (int dcol = -1; dcol <= 1; dcol++) {

        int colPos = col + dcol;

        if (colPos < 0 || colPos >= cols) {
            continue;
        }

        if (dcol == 0) {
            if (board[rowPos][colPos] == empty) {
                possibleMoves.emplace_back(empty, row, col, rowPos, colPos);
            }
        } else {
            if (board[rowPos][colPos] == empty) {
                possibleMoves.emplace_back(empty,row, col, rowPos, colPos);
            } else if (board[rowPos][colPos] == enemyPawns) {
                possibleMoves.emplace_back(enemyPawns, row, col, rowPos, colPos);
            }
        }
    }

    return possibleMoves;
}


std::vector<Move> Board::getLegalMoves(player playerColour) const {
    std::vector<Move> legalMoves;
    legalMoves.reserve(64);
    cell myPawns = playerColour == white_player ? white : black;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] == myPawns) {
                std::vector<Move> singlePawnMoves = getPossibleMovesForSinglePawn(col, row, playerColour);

                legalMoves.insert(legalMoves.end(), singlePawnMoves.begin(), singlePawnMoves.end());
            }
        }
    }

    return legalMoves;
}

game_state Board::getGameState() const {
    for (int col = 0; col < cols; col++) {
        if (board[0][col] == black){
            return black_won;
        }
        if (board[rows - 1][col] == white) {
            return white_won;
        }
    }
    return ongoing;
}

cell Board::getCell(int x, int y) const {
    return board[x][y];
}

void Board::makeMove(const Move &move) {
    board[move.toRow][move.toCol] = board[move.fromRow][move.fromCol];
    board[move.fromRow][move.fromCol] = empty;
}

void Board::undoMove(const Move &move) {
    board[move.fromRow][move.fromCol] = board[move.toRow][move.toCol];
    board[move.toRow][move.toCol] = move.capturedCell;
}


//gettery
const std::vector<std::vector<cell> > &Board::getBoard() const {
    return board;
}


int Board::getCols() const {
    return cols;
}

int Board::getRows() const {
    return rows;
}

//wypisywanie
std::string Board::toString() const {
    std::string result;

    for (int row = rows - 1; row >= 0; row--) {
        result += "| ";
        for (int col = 0; col < cols; col++) {

            char c = cellToString(board[row][col]);

            result += c;
            result += " | ";
        }
        result += '\n';
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    return os << board.toString();
}

std::string to_string(game_state state) {
    switch (state) {
        case black_won: return "black_won";
        case white_won: return "white_won";
        case ongoing: return "ongoing";
    }
    return "";
}
