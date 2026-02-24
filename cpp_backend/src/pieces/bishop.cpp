#include "bishop.h"
#include "board.h"

Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

char Bishop::getSymbol() const {
    return isWhitePiece() ? SYMBOL : std::tolower(SYMBOL);
}

std::vector<Move> Bishop::generateMoves(int row, int col, const Board& board) const {
    std::vector<Move> moves;

    // 4 diagonal directions:
    static const int directions[4][2] = {
        {-1, -1}, {-1, 1},
        {1, -1},  {1, 1}
    };

    for (const auto& [dr, dc] : directions) {
        int r = row + dr;
        int c = col + dc;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* target = board.getPiece(r, c);

            if (!target) {
                moves.push_back({row, col, r, c}); // move to empty square
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