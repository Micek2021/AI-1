//
// Created by mikol on 21.04.2026.
//

#ifndef MOVE_H
#define MOVE_H

#include <string>

enum cell {
    empty,
    white,
    black
};

char cellToString(cell c);

class Move {
public:
    cell capturedCell;
    int fromRow, fromCol, toRow, toCol;

    Move(cell c, int fromRow, int fromCol, int toRow, int toCol);

    [[nodiscard]] std::string toString() const;
};

std::ostream &operator<<(std::ostream &os, const Move &move);



#endif //MOVE_H
