#include "evaluate.h"
#include <cctype> // for std::tolower

// TODO: Implement
int Evaluator::evaluate(const Board& board, bool whiteToMove) {
    int score = 0;
    if (board.isCheckmate(whiteToMove)) {
        return std::numeric_limits<int>::max();
    } else if (board.isCheckmate(!whiteToMove)) {
        return std::numeric_limits<int>::min();
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(i, j);
            if (piece) {
                if (std::isupper(piece->getSymbol()) == whiteToMove) {
                    score += getPieceValue(tolower(piece->getSymbol()));
                } else {
                    score += getPieceValue(tolower(piece->getSymbol()));
                }
            }
        }
    }

    return score;
}
