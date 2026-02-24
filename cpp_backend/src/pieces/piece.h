#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "../move.h"

class Board;

// A piece on a chessboard
class Piece {
public:
    explicit Piece(bool isWhite) : isWhite(isWhite), hasMoved(false) {}
    virtual ~Piece() = default;

    bool isWhitePiece() const { return isWhite; }

    bool getHasMoved() const { return hasMoved; }
    void setHasMoved(bool moved) { hasMoved = moved; }

    virtual char getSymbol() const = 0;
    virtual std::vector<Move> generateMoves(int row, int col, const Board& board) const = 0;

protected:
    bool isWhite;
    bool hasMoved;
};

#endif