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

                    // Defensive bounds check
                    if (move.toRow >= 0 && move.toRow < 8 &&
                        move.toCol >= 0 && move.toCol < 8 &&
                        move.fromRow >= 0 && move.fromRow < 8 &&
                        move.fromCol >= 0 && move.fromCol < 8) {
                        allMoves.push_back(move);
                    } else {
                        std::cerr << "Invalid move generated: from (" << move.fromRow << "," << move.fromCol
                                  << ") to (" << move.toRow << "," << move.toCol << ")" << std::endl;
                    }
                }
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

// Generate moves for search, which are legal moves sorted by a score (captures prioritized)
std::vector<Move> MoveGenerator::generateSearchMoves(const Board& board, bool whiteToMove) {
    std::vector<Move> legalMoves = generateLegalMoves(board, whiteToMove);

    // Precompute score values to use in sort below
    for (Move& move : legalMoves) {
        int val = getCaptureValue(move.capturedPiece);

        if (val == 0) {
            // Just simply moved the piece
            // TODO: Maybe implement preference of moving some pieces over other. eg. don't move king
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