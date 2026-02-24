#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board; // otherwise circular

class Pawn : public Piece {
public:
    static constexpr char SYMBOL = 'P';
    explicit Pawn(bool isWhite);

    char getSymbol() const override;
    std::vector<Move> generateMoves(int row, int col, const Board& board) const override;
};

#endif 
