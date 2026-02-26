#include "search.h"
#include "movegen.h"
#include "evaluate.h"
#include <limits>
#include <iostream>

namespace Search {
    // Forward declaration
    int minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth);
    
    // TODO: Implement  
    Move findBestMove(Board& board, bool whiteToMove, int depth) {
        std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(board, whiteToMove);
        Evaluator evaluator;
        int bestEval = whiteToMove ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        std::cout<<"hi"<<std::endl;
        Move bestMove = legalMoves[0]; // Having 0 shouldn't be possible because that maens it's already checkmate

        for (const Move& move : legalMoves) {
            Board boardCopy = board;
            boardCopy.makeMove(move);
            std::cout<<std::endl<<"Trying: "<<move.fromRow<<" "<<move.fromCol<<" "<<move.toRow<<" "<<move.toCol<<std::endl;
            int eval = minimax(boardCopy, depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), !whiteToMove, evaluator, depth);

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

    // TODO: Implement
    // TODO: Add pruning!
    // TODO: undo moves instead of copying board (pass by reference with undoing)
    int minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth) {
        std::vector<Move> moves = MoveGenerator::generateLegalMoves(board, maximizingPlayer);
        if (moves.empty() || board.isCheckmate(maximizingPlayer)) {
            return maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max(); // checkmate
        }
        if(board.isCheckmate(!maximizingPlayer)) {
            return !maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max(); // checkmate
        }

        if (depth == 0) {
            return evaluator.evaluate(board, maximizingPlayer);
        }

        int bestEval = maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        std::cout<<" Minimax call: Depth "<< depth <<" white to move? "<<maximizingPlayer<<std::endl;

        for (const Move& move : moves) {
            Board boardCopy = board;
            boardCopy.makeMove(move, true);
            
            std::cout<<move.fromRow<<" "<<move.fromCol<<" "<<move.toRow<<" "<<move.toCol<<std::endl;

            int eval = minimax(boardCopy, depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), !maximizingPlayer, evaluator, depth);

            if (maximizingPlayer) {
                if (eval > bestEval) {
                    bestEval = eval;
                }
            } else {
                if (eval < bestEval) {
                    bestEval = eval;
                }
            }
        }
        return bestEval;
    }

    // TODO: Implement
    int scoreMoveStatic(Board board, const Move& move) {
        return -1;
    }

    // TODO: Implement
    int scoreMoveWithSearch(Board board, const Move& move, int depth, bool whiteToMove) {
        return -1;
    }
} // namespace Search