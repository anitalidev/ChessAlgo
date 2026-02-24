#include "movegen.h"
#include "pieces/piece.h"

// Generate all legal moves for the player
std::vector<Move> MoveGenerator::generateLegalMoves(const Board& board, bool whiteToMove) {
    std::vector<Move> pseudoMoves = generateMoves(board, whiteToMove);
    return filterLegalMoves(board, pseudoMoves, whiteToMove);
}

// Generate all pseudo-legal moves for the player
std::vector<Move> MoveGenerator::generateMoves(const Board& board, bool whiteToMove) {
    std::vector<Move> allMoves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.getPiece(row, col);
            if (piece && piece->isWhitePiece() == whiteToMove) {
                std::vector<Move> pieceMoves = piece->generateMoves(row, col, board);
                allMoves.insert(allMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    return allMoves;
}

// Remove moves that would leave the player's king in check
std::vector<Move> MoveGenerator::filterLegalMoves(const Board& board, const std::vector<Move>& pseudoMoves, bool whiteToMove) {
    std::vector<Move> legalMoves;

    for (const Move& move : pseudoMoves) {
        Board copy = board;
        copy.makeMove(move, true);  // simulate/"try out" the move

        if (!copy.isKingInCheck(whiteToMove)) {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}