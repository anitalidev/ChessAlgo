#include "search.h"
#include "movegen.h"
#include "evaluate.h"
#include <limits>
#include <iostream>

namespace Search {
    static const int MAX_DEPTH = 64; // Probably will never end up using this much

    static Move killerMoves[MAX_DEPTH][2];
    // To store quiet (non-capture) moves that killed using beta <= alpha in previous (maybe-siblings/cousins)
    // So that they are sorted over other ones in future move orderings
    // Not much need to clear between searches

    // All nodes at a depth will either ALL be min/max nodes, so no need to store two.


    // Forward declarations
    // IMPORTANT: With current implementation, maxDepth must stay constant through all related calls
    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth);
    std::vector<Move> generateSearchMoves(const Board& board, int ply, bool whiteToMove);
    
    Move findBestMove(Board& board, bool whiteToMove, int depth) {
        std::vector<Move> legalMoves = generateSearchMoves(board, 0, whiteToMove);
        Evaluator evaluator;
        int bestEval = whiteToMove ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        if (legalMoves.empty()) return Move();
        Move bestMove = legalMoves[0]; 

        for (const Move& move : legalMoves) {
            Board boardCopy = board;
            boardCopy.makeMove(move);
            int eval = minimax(boardCopy, depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), !whiteToMove, evaluator, depth);

            // For testing if needed: 
            // std::cout<<move.fromRow<<" "<<move.fromCol<<" "<<move.toRow<<" "<<move.toCol<<" "<<eval<<std::endl;

            if (whiteToMove) {
                if (eval > bestEval) {
                    bestEval = eval;
                    bestMove = move;
                }
            } else {
                if (eval < bestEval) {
                    bestEval = eval;
                    bestMove = move;
                }
            }
        }

        return bestMove;
    }

    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth) {
        // LATER: Check stalemate
        if (depth == 0) {
            return evaluator.evaluate(board);
        }

        std::vector<Move> moves = generateSearchMoves(board, maxDepth - depth, maximizingPlayer);
        if (moves.empty() && board.isCheckmate(maximizingPlayer)) {
            return maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max(); // checkmate
        }
        if(board.isCheckmate(!maximizingPlayer)) {
            return !maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max(); // checkmate
        }

        int bestEval = maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

        for (const Move& move : moves) {
            board.makeMove(move, true);                
            int eval = minimax(board, depth - 1, alpha, beta, !maximizingPlayer, evaluator, depth);
            board.undoMove();

            if (maximizingPlayer) {
                if (eval > bestEval) {
                    bestEval = eval;
                }
                alpha = std::max(alpha, eval); // You are a maximizing node so you would like to maximize the eval

                if (beta <= alpha) {
                    if (!board.getPiece(move.toRow, move.toCol)) {
                        killerMoves[maxDepth - depth][1] = killerMoves[maxDepth - depth][0];
                        killerMoves[maxDepth - depth][0] = move;
                    }
                    break; // if beta <= alpha, that means your parent (a minimizer) has found a path with value beta,
                    // and since it wants to minimze, then it will never choose you, alpha, since you're maximizing
                    // so your alpha only goes up. 
                }
            } else {
                if (eval < bestEval) {
                    bestEval = eval; 
                }
                beta = std::min(beta, eval); // You are a minimizing node so you would like to maximize the eval

                if (beta <= alpha) {
                    if (!board.getPiece(move.toRow, move.toCol)) {
                        killerMoves[maxDepth - depth][1] = killerMoves[maxDepth - depth][0];
                        killerMoves[maxDepth - depth][0] = move;
                    }
                    break; 
                }
            }
        }
        return bestEval;
    } 

    // Generate moves for a search, which are legal moves sorted by a score (captures prioritized)
    // NOTE: This method of sorting favours trading pieces over passive playing which is... interesting to note!
    std::vector<Move> generateSearchMoves(const Board& board, int ply, bool whiteToMove) {
        std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(board, whiteToMove);

        // Precompute score values to use in sort below
        for (Move& move : legalMoves) {
            if (move == Search::killerMoves[ply][0]) {
                move.score = 5000; // rather large score, 0 = more recent killer move
                continue;
            } 
            if (move == Search::killerMoves[ply][1]) {
                move.score = 4999; // one less than above
                continue;
            }

            Piece* captured = board.getPiece(move.toRow, move.toCol);
            Piece* moving = board.getPiece(move.fromRow, move.fromCol);
            int val;

            if (captured) {
                val = 10 * getCaptureValue(captured->getSymbol());
                val -= getCaptureValue(moving->getSymbol()); // If causes error something is very wrong.
                // ^ We prefer taking with smaller value pieces (tends to be safer/better)
            } else {
                val = 0;
            }

            move.score = val;
        }

        // Sort moves by their score value. 
        sort(legalMoves.begin(), legalMoves.end(), [](const Move& moveA, const Move& moveB) {
            return moveA.score > moveB.score;
        });

        return legalMoves;
    }

    int getCaptureValue(char symbol) {
        switch (tolower(symbol)) {
            case 'p': return 100;   // Pawn
            case 'n': return 320;   // Knight
            case 'b': return 330;   // Bishop
            case 'r': return 500;   // Rook
            case 'q': return 900;   // Queen
            case 'k': return 20000;   // King
            default: return 0;
        }
    }
} // namespace Search