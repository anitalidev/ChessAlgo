#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board;

class Queen : public Piece {
public:
    static constexpr char SYMBOL = 'Q';
    explicit Queen(bool isWhite);

    char getSymbol() const override;
    std::vector<Move> generateMoves(int row, int col, const Board& board) const override;
};

#endif 