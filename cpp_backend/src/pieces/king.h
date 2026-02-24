#ifndef KING_H
#define KING_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board;

class King : public Piece {
public:
    static constexpr char SYMBOL = 'K';
    explicit King(bool isWhite);

    char getSymbol() const override;
    std::vector<Move> generateMoves(int row, int col, const Board& board) const override;
};

#endif 
