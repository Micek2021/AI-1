//
// Created by mikol on 21.04.2026.
//

#include "move.h"

Move::Move(cell c, int fromRow, int fromCol, int toRow, int toCol) : capturedCell(c), fromRow(fromRow), fromCol(fromCol), toRow(toRow), toCol(toCol){}


char cellToString(cell c) {
    switch (c) {
        case empty: return '-';
        case white: return 'W';
        case black: return 'B';
    }
    return '?';
}

std::string Move::toString() const {
    std::string result;

    result += "(";
    result += std::to_string(fromCol);
    result += ", ";
    result += std::to_string(fromRow);
    result += ") -> {";
    result += std::to_string(toCol);
    result += ", ";
    result += std::to_string(toRow);
    result += "} ";

    result += "Captured cell: ";
    result += cellToString(capturedCell);


    return result;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    return os << move.toString();
}

