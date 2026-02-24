#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board;

class Knight : public Piece {
public:
    static constexpr char SYMBOL = 'N';
    explicit Knight(bool isWhite);

    char getSymbol() const override;
    std::vector<Move> generateMoves(int row, int col, const Board& board) const override;
};

#endif 