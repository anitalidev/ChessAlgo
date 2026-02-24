package engine;

public class BackendBridge {
    static {
        System.loadLibrary("ChessEngine"); // Name of your C++ shared library
    }

    public static native boolean applyMove(String move);
    public static native String[][] getBoardState();
    public static native void loadFEN(String fen);
    public static native boolean isCheckmate();
    public static native String[] getLegalMoves();
    public static native String getSuggestedMove();
}
