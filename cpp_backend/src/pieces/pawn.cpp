#include "pieces/pawn.h"
#include "piece.h"   
#include "board.h"          
#include "move.h"
#include <vector>

Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

char Pawn::getSymbol() const {
    return isWhitePiece() ? 'P' : 'p';
}

std::vector<Move> Pawn::generateMoves(int row, int col, const Board& board) const {
    std::vector<Move> moves;

    int direction = isWhitePiece() ? -1 : 1;
    int startRow = isWhitePiece() ? 6 : 1;

    int oneStep = row + direction;
    int twoStep = row + 2 * direction;

    // Move one square forward
    if (oneStep >= 0 && oneStep < 8 && board.getPiece(oneStep, col) == nullptr) {
        moves.push_back({row, col, oneStep, col});

        // Move two squares forward from starting position
        if (row == startRow && board.getPiece(twoStep, col) == nullptr) {
            moves.push_back({row, col, twoStep, col});
        }
    }

    // Diagonal captures (left and right)
    for (int dc : {-1, 1}) {
        int newCol = col + dc;
        if (newCol >= 0 && newCol < 8) {
            Piece* target = board.getPiece(oneStep, newCol);
            if (target != nullptr && target->isWhitePiece() != isWhitePiece()) {
                moves.push_back({row, col, oneStep, newCol});
            }
        }
    }

    // LATER: en passant
    // LATER: promotion

    return moves;
}