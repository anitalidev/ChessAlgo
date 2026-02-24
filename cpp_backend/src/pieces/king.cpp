#include "king.h"
#include "board.h"

King::King(bool isWhite) : Piece(isWhite) {}

char King::getSymbol() const {
    return isWhitePiece() ? SYMBOL : std::tolower(SYMBOL);
}

std::vector<Move> King::generateMoves(int row, int col, const Board& board) const {
    std::vector<Move> moves;

    // Move one space in all 8 directions
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int r = row + dr;
            int c = col + dc;

            if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                Piece* target = board.getPiece(r, c);
                if (!target || target->isWhitePiece() != isWhitePiece()) {
                    moves.push_back({row, col, r, c});
                }
            }
        }
    }

    // TODO: Add castling when rook and king haven't moved

    return moves;
}