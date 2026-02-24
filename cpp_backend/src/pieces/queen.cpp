#include "queen.h"
#include "board.h"

Queen::Queen(bool isWhite) : Piece(isWhite) {}

char Queen::getSymbol() const {
    return isWhitePiece() ? SYMBOL : std::tolower(SYMBOL);
}

std::vector<Move> Queen::generateMoves(int row, int col, const Board& board) const {
    std::vector<Move> moves;

    // 8 directions: diagonals + straight lines
    static const int directions[8][2] = {
        {-1,  0}, {1,  0}, // vertical
        { 0, -1}, {0,  1}, // horizontal
        {-1, -1}, {-1, 1}, // diagonal up
        { 1, -1}, { 1, 1}  // diagonal down
    };

    for (const auto& [dr, dc] : directions) {
        int r = row + dr;
        int c = col + dc;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* target = board.getPiece(r, c);
            if (!target) {
                moves.push_back({row, col, r, c});
            } else {
                if (target->isWhitePiece() != isWhitePiece()) {
                    moves.push_back({row, col, r, c}); // capture
                }
                break; // stop sliding
            }
            r += dr;
            c += dc;
        }
    }

    return moves;
}