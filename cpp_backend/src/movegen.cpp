#include "movegen.h"
#include <iostream>
#include "pieces/piece.h"
#include "search.h"

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
                for (Move& move : pieceMoves) {
                    allMoves.push_back(move);
                }
            }
        } 
    }

    return allMoves;
}

// Remove moves that would leave the player's king in check
std::vector<Move> MoveGenerator::filterLegalMoves(const Board& board, const std::vector<Move>& pseudoMoves, bool whiteToMove) {
    std::vector<Move> legalMoves;
    Board copy = board;

    for (const Move& move : pseudoMoves) {
        copy.makeMove(move, true);  // simulate/"try out" the move

        if (!copy.isKingInCheck(whiteToMove)) {
            legalMoves.push_back(move);
        }

        copy.undoMove();
    }

    return legalMoves;
}