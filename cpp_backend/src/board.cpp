#include "board.h"
#include "move.h"
#include "movegen.h"
#include "pieces/pieces.h"  
#include <iostream>
#include <sstream>
#include <cctype>

Board::Board() {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = nullptr;
}

Board::~Board() {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            delete board[r][c];
}

Piece* Board::getPiece(int row, int col) const {
    return board[row][col];
}

void Board::setPiece(int row, int col, Piece* piece) {
    delete board[row][col];  // Avoid memory leak
    board[row][col] = piece;
}

// TODO: Add guards in case given FEN is invalid. Eg. no king, too many pieces, bad format, etc.,
void Board::loadFEN(const std::string& fen) {

    // Clear the board
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            removePiece(r, c);


    std::istringstream ss(fen);
    std::string boardPart, activeColor;

    ss >> boardPart >> activeColor; // TODO: Add castling rights

    int row = 0, col = 0;

    for (char ch : boardPart) {
        if (ch == '/') {
            ++row;
            col = 0;
        } else if (std::isdigit(ch)) {
            col += ch - '0';
        } else {
            Piece* piece = createPieceFromSymbol(ch);
            if (piece && row < 8 && col < 8) {
                setPiece(row, col, piece);
                ++col;
            }
        }
    }

    whiteToMove = (activeColor == "w");
}

void Board::removePiece(int row, int col) {
    delete board[row][col];
    board[row][col] = nullptr;
}

Piece* Board::createPieceFromSymbol(char symbol) {
    bool isWhite = isupper(symbol);
    char lower = std::tolower(symbol);

    switch (lower) {
        case 'p': return new Pawn(isWhite);
        case 'n': return new Knight(isWhite); 
        case 'b': return new Bishop(isWhite);
        case 'r': return new Rook(isWhite);
        case 'q': return new Queen(isWhite);
        case 'k': return new King(isWhite);
        default: return nullptr;
    }
}

bool Board::isKingInCheck(bool white) const {
    int kingRow = -1;
    int kingCol = -1;

    // Find the king's position
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* piece = board[r][c];
            if (piece && piece->isWhitePiece() == white && std::tolower(piece->getSymbol()) == 'k') { 
                kingRow = r;
                kingCol = c;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1 || kingCol == -1) {
        // King not found, default true but shouldn't happen in a valid game
        return true;
    }

    // Check if any opposing piece can attack the king
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* piece = board[r][c];
            if (piece && piece->isWhitePiece() != white) {
                std::vector<Move> attacks = piece->generateMoves(r, c, *this);
                for (const Move& move : attacks) {
                    if (move.toRow == kingRow && move.toCol == kingCol) {
                        return true; // King is under attack
                    }
                }
            }
        }
    }

    return false; // No threats found
}

// skipValidation can be set true to avoid infinite recursion with generateMoves
bool Board::makeMove(const Move& move, bool skipValidation) {
    Piece* movingPiece = board[move.fromRow][move.fromCol];
    if (!movingPiece || (!skipValidation && movingPiece->isWhitePiece() != whiteToMove))
        return false;

    if (!skipValidation) {
        std::vector<Move> legalMoves = movingPiece->generateMoves(move.fromRow, move.fromCol, *this);
        bool isLegal = false;
        for (const Move& m : legalMoves) {
            if (m.toRow == move.toRow && m.toCol == move.toCol) {
                isLegal = true;
                break;
            }
        }
        if (!isLegal) return false;
    }

    delete board[move.toRow][move.toCol]; // In case something is getting captured
    board[move.toRow][move.toCol] = movingPiece;
    board[move.fromRow][move.fromCol] = nullptr;
    movingPiece->setHasMoved(true);
    whiteToMove = !whiteToMove;

    history.push_back(move);

    return true; 
}

// Undo the last move made. This will require storing a history of moves
// Important to help with search to avoid deep copying boards
// TODO: Make sure that the stored history is maintained properly in other areas,
// such as when needing to reset the history 
bool Board::undoMove() {
    if (history.empty()) {
        return false;
    }
    // TOOD: Below currently assumes the history is correct. Add guards
    // TODO: Fix move so that we can keep piece history and don't have to re-make captured

    Move move = history.back();
    history.pop_back();

    Piece* captured = createPieceFromSymbol(move.capturedPiece);

    board[move.fromRow][move.fromCol] = board[move.toRow][move.toCol];
    board[move.toRow][move.toCol] = captured;

    whiteToMove = !whiteToMove;

    return true;
}

bool Board::isCheckmate(bool white) const {
    if (!isKingInCheck(white)) {
        return false; 
    }

    static MoveGenerator moveGen; // TODO: Decide what to do about MoveGenerator
    std::vector<Move> legalMoves = moveGen.generateLegalMoves(*this, white);

    return legalMoves.empty();
}

// Deep copy constructor
Board::Board(const Board& other) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (other.board[r][c]) {
                char symbol = other.board[r][c]->getSymbol();
                bool isWhite = other.board[r][c]->isWhitePiece();
                switch (std::tolower(symbol)) {
                    case 'p': board[r][c] = new Pawn(isWhite); break;
                    case 'r': board[r][c] = new Rook(isWhite); break;
                    case 'n': board[r][c] = new Knight(isWhite); break;
                    case 'b': board[r][c] = new Bishop(isWhite); break;
                    case 'q': board[r][c] = new Queen(isWhite); break;
                    case 'k': board[r][c] = new King(isWhite); break;
                    default:  board[r][c] = nullptr; break;
                }
                board[r][c]->setHasMoved(other.board[r][c]->getHasMoved());
            } else {
                board[r][c] = nullptr;
            }
        }
    }

    whiteToMove = other.whiteToMove;
}

bool Board::getWhiteToMove() {
    return whiteToMove;
}

// So far only for testing:
void Board::print() const {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board[r][c];
            if (p)
                std::cout << p->getSymbol();
            else
                std::cout << '.';
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}