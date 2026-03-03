#include "evaluate.h"
#include <cctype> // for std::tolower

// Evaluate board state. More positive = whiteToMove better, More negative = whiteToMove better
int Evaluator::evaluate(const Board& board) {
    int score = 0;
    bool white = board.getWhiteToMove();
    if (board.isCheckmate(white)) {
        return -100000;
    } else if (board.isCheckmate(!white)) {
        return 100000;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(i, j);
            if (piece) {
                if (std::isupper(piece->getSymbol()) == white) {
                    score += getPieceValue(tolower(piece->getSymbol()));
                } else {
                    score -= getPieceValue(tolower(piece->getSymbol()));
                }
            }
        }
    }

    return score;
}
