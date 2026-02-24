#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <iostream> // For debugging
#include <vector>
#include "board.h"
#include "move.h"

class MoveGenerator {
public:
    // Generate all pseudo-legal moves for the player (white or black)
    std::vector<Move> generateMoves(const Board& board, bool whiteToMove);

    // Filter out illegal moves like those that leave the king in check
    std::vector<Move> filterLegalMoves(const Board& board, const std::vector<Move>& pseudoMoves, bool whiteToMove);

    // Generate all legal moves for the player (white or black)
    std::vector<Move> generateLegalMoves(const Board& board, bool whiteToMove);
};

#endif