## Planning (Flexible)

### Phase 1: Core Chess Engine (C++)
Build the backend engine responsible for evaluating board positions and suggesting moves using search algorithms.

**Objectives:**
v Represent the chess board using FEN notation 
v Implement legal move generation for all piece types  
- Build a working Minimax algorithm with alpha-beta pruning
- Design a simple command-line interface to input positions and return the best move  

### Phase 2: Java GUI Front-End
Create an interactive Java-based graphical interface for user interaction.

**Objectives:**
- Design a clean chessboard using Swing or JavaFX  
- Allow player move input through mouse interaction  
- Display game state, move history, and legal highlights  
- Communicate with the C++ engine to send current position and receive best move suggestions

---

### Phase 3: C++ – Java Integration
Enable real-time interaction between the GUI and backend engine.

**Objectives:**
- Connect the Java GUI to the C++ engine via one of the following:
  - TCP socket communication (preferred)
  - File-based exchange
  - Java `ProcessBuilder` to run C++ and capture output
- Ensure move validation and board sync between both sides  
- Handle game flow: player vs AI, AI vs AI, or analysis mode

### Phase 4: Wrap-Up
Wrap-Up project and add final changes

**Objectives:**
- Improve readability or refactor if/when necessary
- Work on README.md