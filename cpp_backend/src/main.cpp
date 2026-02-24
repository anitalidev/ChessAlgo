#include <iostream>
#include <string>
#include "board.h"
#include "move.h"
#include "movegen.h"
#include "search.h" 

int main() {
    Board board;
    MoveGenerator gen;

    std::string fen;
    std::cout << "Enter FEN position (or type 'exit'):\n";

    while (true) {
        std::getline(std::cin, fen);
        if (fen == "exit") break;

        board.loadFEN(fen);

        bool whiteToMove = fen.find(" w ") != std::string::npos;

        // Generate legal moves
        std::vector<Move> pseudoMoves = gen.generateMoves(board, whiteToMove);
        std::vector<Move> legalMoves = gen.filterLegalMoves(board, pseudoMoves, whiteToMove);

        if (legalMoves.empty()) {
            std::cout << "No legal moves available.\n";
            continue;
        }

        // Run minimax search with alpha-beta
        Move bestMove = Search::findBestMove(board, whiteToMove, 3); // 3-ply search depth
        std::cout << "Best move: "
                  << char('a' + bestMove.fromCol) << (8 - bestMove.fromRow)
                  << " -> "
                  << char('a' + bestMove.toCol) << (8 - bestMove.toRow) << "\n";
    }

    return 0;
}