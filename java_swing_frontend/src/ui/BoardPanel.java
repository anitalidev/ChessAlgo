package ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class BoardPanel extends JPanel {
    private static final int TILE_SIZE = 64;
    private String[][] board = new String[8][8];

    private Point selectedSquare = null;
    private Point suggestedFrom = null;
    private Point suggestedTo = null;

    private java.util.List<Point> legalMoves = new ArrayList<>();

    public BoardPanel() {
        setupStartingPosition();

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                int row = e.getY() / TILE_SIZE;
                int col = e.getX() / TILE_SIZE;
                handleClick(row, col);
            }
        });
    }

    private void handleClick(int row, int col) {
        if (selectedSquare == null) {
            java.util.List<Point> foundMoves = getLegalDestinationsFrom(row, col);
            if (foundMoves.isEmpty()) return; // No legal moves. Don't select square

            selectedSquare = new Point(row, col);
            legalMoves = foundMoves;
        } else {
            Point from = selectedSquare;
            Point to = new Point(row, col);

            if (from.x == to.x && from.y == to.y) { // If clicked the same square
                selectedSquare = null;
                legalMoves.clear();
                repaint();
                suggestedFrom = null;
                suggestedTo = null;
                return;
            }

            if (legalMoves.contains(to)) { // Don't make extra calls if obviously illegal move
                ChessApp.makeMove(from, to); // won't make move if illegal
            } else {
                selectedSquare = null;
                legalMoves.clear();
                handleClick(row, col); // Possibly select current square if allowed. 
                return; // Shouldn't redo below
            }
            selectedSquare = null;
            legalMoves.clear();
        }

        suggestedFrom = null;
        suggestedTo = null;

        repaint();
    }

    private void setupStartingPosition() {
        board[0] = new String[] { "r", "n", "b", "q", "k", "b", "n", "r" };
        board[1] = new String[] { "p", "p", "p", "p", "p", "p", "p", "p" };

        for (int r = 2; r <= 5; r++)
            board[r] = new String[] { null, null, null, null, null, null, null, null };

        board[6] = new String[] { "P", "P", "P", "P", "P", "P", "P", "P" };
        board[7] = new String[] { "R", "N", "B", "Q", "K", "B", "N", "R" };
    }

    public void updateBoard(String[][] newBoard) {
        this.board = newBoard;
        repaint();
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(8 * TILE_SIZE, 8 * TILE_SIZE);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // Draws out the tiles of the chessboard and pieces
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                // Tiles have a checkerboard pattern
                boolean isLight = (row + col) % 2 == 0;
                g.setColor(isLight ? new Color(240, 217, 181) : new Color(181, 136, 99));
                g.fillRect(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE);

                // Highlight legal moves for selected piece (if there is one) as translucent green
                if (legalMoves.contains(new Point(row, col))) {
                    g.setColor(new Color(0, 255, 0, 100)); // translucent green
                    g.fillRect(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                }

                // Highlight the suggested move as translucent orange
                if ((suggestedFrom != null && new Point(row, col).equals(suggestedFrom)) ||
                        (suggestedTo != null && new Point(row, col).equals(suggestedTo))) {
                    g.setColor(new Color(255, 165, 0, 120)); // translucent orange
                    g.fillRect(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                }

                // TODO: Highlight king with red, if in check. Low priority

                // if there's a piece on this tile, draw it
                String code = board[row][col];
                if (code != null) {
                    ImageIcon icon = PieceIconLoader.getIcon(code); // loads images from resources/ folder
                    g.drawImage(icon.getImage(), col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, null);
                }
            }
        }
    }

    private java.util.List<Point> getLegalDestinationsFrom(int row, int col) {
        // TODO: Implement getting legal moves from just one square instead of having to filter legal moves for all squares
        if (board[row][col] == null || Character.isUpperCase(board[row][col].charAt(0)) != ChessApp.whiteToMove())
                return new ArrayList<>(); // not legal to "move" an empty square or piece of different colour

        java.util.List<Point> moves = new ArrayList<>();

        String[] allMoves = engine.BackendBridge.getLegalMoves();

        String fromCoord = toAlgebraic(new Point(row, col));

        for (String move : allMoves) {
            if (move.startsWith(fromCoord)) {
                String to = move.substring(2, 4);
                Point toPoint = fromAlgebraic(to);
                moves.add(toPoint);
            }
        }

        return moves;
    }

    // Inverse of below 
    private static String toAlgebraic(Point p) {
        char file = (char) ('a' + p.y);
        int rank = 8 - p.x;
        return "" + file + rank;
    }

    // Converting portions of FEN (eg. "a2", "e4") to Point(row, col)
    // eg. "a2" -> Point(6, 0) since row 6 is the second to last row and column 0 is the 'a' file
    // Note: On chessboard, row 1 is on the BOTTOM
    private static Point fromAlgebraic(String s) {
        int col = s.charAt(0) - 'a';
        int row = 8 - Character.getNumericValue(s.charAt(1));
        return new Point(row, col);
    }

    // Ask the CPP backend for the suggested move given the current board state
    public void generateSuggestedMove() {
        String move = engine.BackendBridge.getSuggestedMove();
        if (move != null && move.length() == 4) {
            suggestedFrom = fromAlgebraic(move.substring(0, 2));
            suggestedTo = fromAlgebraic(move.substring(2, 4));
            repaint(); // "Refresh" to show the suggested move highlighted on board
        }
    }

    public void loadFEN(String fen) {
        String[] parts = fen.split(" ");
        if (parts.length < 1)
            return;

        String[] rows = parts[0].split("/");
        for (int r = 0; r < 8; r++) {
            String row = rows[r];
            int c = 0;
            for (char ch : row.toCharArray()) {
                if (Character.isDigit(ch)) {
                    int emptyCount = ch - '0';
                    for (int i = 0; i < emptyCount; i++) {
                        board[r][c++] = null;
                    }
                } else {
                    board[r][c++] = String.valueOf(ch);
                }
            }
        }

        // reset
        selectedSquare = null;
        legalMoves.clear();
        suggestedFrom = null;
        suggestedTo = null;
        repaint(); // Update the board with the new positions from the FEN string
    }
}