//
// Created by mikol on 21.04.2026.
//

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "board.h"

/*
 * PLIK POCZĄTKOWO ZAWIERAŁ WSZYSTKIE ZDEFINIOWANEGO HEURYSTYKI
 * TERAZ DZIAŁA JAKO ŚCIĄGA JAK DZIAŁA KAŻDA POJEDYŃCZO
 * ZOSTAŁ ZASTĄPIONY EWALUATOREM W CELACH OPTYMALIZACYJNYCH
 */


class Heuristic {
public:
    [[nodiscard]] virtual int evaluate(const Board& board, player p) const = 0;
    virtual ~Heuristic() = default;
};

/*
 * Offense
 */
//Advancement of the whole thing
class Advancement : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};

//Advancement of the largest pawn
class MostAdvanced : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};

/*
 * Positioning / state of the game
 */
// control of the centre
class CentreControl : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};

class SideControl : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};

class CountPawns : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};
/*
 * Defence
 */

//Covering the whole board
class Coverage : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};

/*
 * WINNING
 */
//If you can end, do so
class GuaranteedWin : public Heuristic {
public:
    [[nodiscard]] int evaluate(const Board& board, player p) const override;
};

#endif //HEURISTICS_H