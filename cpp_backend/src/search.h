#ifndef SEARCH_H
#define SEARCH_H

#include "move.h"
#include "board.h"

namespace Search {
    Move findBestMove(Board& board, bool whiteToMove, int depth);

    int scoreMoveWithSearch(Board board, const Move& move, int depth, bool whiteToMove);

    int scoreMoveStatic(Board board, const Move& move);

    // Sort helper: Returns capture value of symbol
    int getCaptureValue(char symbol);
}

#endif // SEARCH_H