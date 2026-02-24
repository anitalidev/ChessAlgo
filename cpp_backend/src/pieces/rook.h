#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board;

class Rook : public Piece {
public:
    static constexpr char SYMBOL = 'R';
    explicit Rook(bool isWhite);

    char getSymbol() const override;
    std::vector<Move> generateMoves(int row, int col, const Board& board) const override;
};

#endif 