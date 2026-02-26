#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <iostream> // For debugging
#include <vector>
#include "board.h"
#include "move.h"

class MoveGenerator {
public:
    // Generate all pseudo-legal moves for the player (white or black)
    std::vector<Move> static generateMoves(const Board& board, bool whiteToMove);

    // Generate all legal moves for the player (white or black)
    std::vector<Move> static generateLegalMoves(const Board& board, bool whiteToMove);

    // Generate all legal moves but order them in decreasing order of captured piece due to move (nothing captured = last)
    std::vector<Move> static generateSearchMoves(const Board& board, bool whiteToMove);

private: 
    // Filter out illegal moves like those that leave the king in check
    std::vector<Move> static filterLegalMoves(const Board& board, const std::vector<Move>& pseudoMoves, bool whiteToMove);

    // Sort helper: Returns capture value of symbol
    int static getCaptureValue(char symbol) {
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
    
};

#endif