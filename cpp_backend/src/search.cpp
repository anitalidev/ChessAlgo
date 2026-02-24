#include "search.h"
#include "movegen.h"
#include "evaluate.h"
#include <limits>
#include <iostream>

namespace Search {

    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth);

    // TODO: Implement 
    Move findBestMove(Board& board, bool whiteToMove, int depth) {
        Move bestMove;
        return bestMove;
    }

    // TODO: Implement
    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer, Evaluator& evaluator, int maxDepth) {
        return -1;
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