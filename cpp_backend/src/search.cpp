#include "search.h"
#include "movegen.h"
#include "evaluate.h"
#include <limits>
#include <iostream>

namespace Search {
    // Forward declaration
    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth);
    
    Move findBestMove(Board& board, bool whiteToMove, int depth) {
        std::vector<Move> legalMoves = MoveGenerator::generateSearchMoves(board, whiteToMove);
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

        std::vector<Move> moves = MoveGenerator::generateSearchMoves(board, maximizingPlayer);
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

                if (beta <= alpha)
                    break; // if beta <= alpha, that means your parent (a minimizer) has found a path with value beta,
                    // and since it wants to minimze, then it will never choose you, alpha, since you're maximizing
                    // so your alpha only goes up. 
            } else {
                if (eval < bestEval) {
                    bestEval = eval; 
                }
                beta = std::min(beta, eval); // You are a minimizing node so you would like to maximize the eval

                if (beta <= alpha)
                    break; 
            }
        }
        return bestEval;
    }
} // namespace Search