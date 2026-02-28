#include "movegen.h"
#include <iostream>
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
                for (Move& move : pieceMoves) {
                    move.movingPiece = piece->getSymbol();
                    Piece* capt = board.getPiece(move.toRow, move.toCol);
                    if (capt) move.capturedPiece = capt->getSymbol();
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

// Generate moves for search, which are legal moves sorted by a score (captures prioritized)
std::vector<Move> MoveGenerator::generateSearchMoves(const Board& board, bool whiteToMove) {
    std::vector<Move> legalMoves = generateLegalMoves(board, whiteToMove);

    // Precompute score values to use in sort below
    for (Move& move : legalMoves) {
        int val = getCaptureValue(move.capturedPiece);

        if (val == 0) {
            // Just simply moved the piece
        } else {
            val -= getCaptureValue(move.movingPiece); // Capturing with smaller value is less risky
        }

        move.score = val;
    }

    // Sort moves by their score value. 
    sort(legalMoves.begin(), legalMoves.end(), [](const Move& moveA, const Move& moveB) {
        return moveA.score > moveB.score;
    });

    return legalMoves;
}