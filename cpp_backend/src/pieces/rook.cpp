#include "rook.h"
#include "board.h"

Rook::Rook(bool isWhite) : Piece(isWhite) {}

char Rook::getSymbol() const {
    return isWhitePiece() ? SYMBOL : std::tolower(SYMBOL);
}

std::vector<Move> Rook::generateMoves(int row, int col, const Board& board) const {
    std::vector<Move> moves;

    // All possible directions for Rook to move in
    static const int directions[4][2] = {
        {0, -1}, {0, 1},
        {1, 0},  {-1, 0}
    };

    for (const auto& [dr, dc] : directions) {
        int r = row + dr;
        int c = col + dc;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* target = board.getPiece(r, c);

            if (!target) {
                moves.push_back({row, col, r, c}); // move to blank space
            } else {
                if (target->isWhitePiece() != isWhitePiece()) {
                    moves.push_back({row, col, r, c}); // capture
                }
                break; // blocked
            }

            r += dr;
            c += dc;
        }
    }

    return moves;
}
