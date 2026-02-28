#ifndef MOVE_H
#define MOVE_H

struct Move {
    int fromRow, fromCol, toRow, toCol;
    char movingPiece, capturedPiece;
    // TODO: After finalizing UndoState and editing movegen, can remove capturedPiece.
    int score = 0;

    Move() : fromRow(0), fromCol(0), toRow(0), toCol(0) {}
    
    Move(int fr, int fc, int tr, int tc) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), movingPiece('.'), capturedPiece('.') {} 
    // '.' = empty square

    Move(int fr, int fc, int tr, int tc, char mp) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), movingPiece(mp), capturedPiece('.') {} 
    // '.' = empty square

    Move(int fr, int fc, int tr, int tc, char mp, char cp) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), movingPiece(mp), capturedPiece(cp) {} 
};

#endif