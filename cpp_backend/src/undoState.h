#include "move.h"
#include "pieces/piece.h"

struct UndoState {
    Move move;
    Piece* capturedPiece;
    bool hadMoved;
    // Add whiteToMove if needed

    UndoState(Move m, Piece* cp, bool hm) : move(m), capturedPiece(cp), hadMoved(hm) {} 
};