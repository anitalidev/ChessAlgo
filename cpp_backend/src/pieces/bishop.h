#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board;

class Bishop : public Piece {
public:
    static constexpr char SYMBOL = 'B';
    explicit Bishop(bool isWhite);

    char getSymbol() const override;
    std::vector<Move> generateMoves(int row, int col, const Board& board) const override;
};

#endif 
