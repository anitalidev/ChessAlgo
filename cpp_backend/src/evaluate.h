    #ifndef EVALUATE_H
    #define EVALUATE_H

    #include "board.h"

    class Evaluator {
    public:
        // Returns positive score for white advantage, negative for black
        int evaluate(const Board& board);

    private:
        // Helper: material value of each piece
        int getPieceValue(char symbol);
    };

    #endif
