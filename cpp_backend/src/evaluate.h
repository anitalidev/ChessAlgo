    #ifndef EVALUATE_H
    #define EVALUATE_H

    #include "board.h"

    class Evaluator {
    public:
        // Returns positive score for white advantage, negative for black
        int evaluate(const Board& board, bool whiteToMove);

    private:
        // Helper: material value of each piece
        private:
        // Helper: material value of each piece
        int getPieceValue(char symbol) {
            switch (tolower(symbol)) {
                case 'p': return 100;   // Pawn
                case 'n': return 320;   // Knight
                case 'b': return 330;   // Bishop
                case 'r': return 500;   // Rook
                case 'q': return 900;   // Queen
                case 'k': return 0;     // King (usually not counted in material)
                default: return 0;
            }
        }
    };

    #endif
