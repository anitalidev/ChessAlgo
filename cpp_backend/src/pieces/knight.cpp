#include "knight.h"
#include "board.h"

Knight::Knight(bool isWhite) : Piece(isWhite) {}

char Knight::getSymbol() const {
    return isWhitePiece() ? SYMBOL : std::tolower(SYMBOL);
}

std::vector<Move> Knight::generateMoves(int row, int col, const Board& board) const {
    std::vector<Move> moves;

    // All 8 possible knight moves
    static const int directions[8][2] = {
        {-2, -1}, {-2,  1},
        {-1, -2}, {-1,  2},
        { 1, -2}, { 1,  2},
        { 2, -1}, { 2,  1}
    };

    for (const auto& [dr, dc] : directions) {
        int r = row + dr;
        int c = col + dc;

        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* target = board.getPiece(r, c);
            if (target == nullptr || target->isWhitePiece() != isWhitePiece()) {
                moves.push_back({row, col, r, c});
            }
        }
    }

    return moves;
}