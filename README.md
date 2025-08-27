# XOX Game: Minimax Algorithm Implementation
### MSc Data Science & Engineering · Artificial Intelligence Course · Project 2/2: Game Construction
A two-player strategic game implementation in C featuring an optimal AI opponent using the Minimax algorithm on a 4×3 grid with unique XOX/OXO triad-based victory conditions.

## Overview

This project implements a variant of tic-tac-toe on a 4×3 grid where victory is determined by forming triads (XOX or OXO patterns) rather than traditional three-in-a-row. The computer plays as MAX (X) using the Minimax algorithm to ensure optimal play, while the human player plays as MIN (O).

## Game Rules

### Board Setup
- **Grid size**: 4 rows × 3 columns (12 total positions)
- **Initial state**: One X and one O placed randomly in non-adjacent positions
- **Turn order**: MAX (Computer/X) plays first, then MIN (Human/O)

### Victory Conditions
The game ends when triads are formed, evaluated by counting:
- **XOX triads**: Count toward MAX player victory
- **OXO triads**: Count toward MIN player victory

**Final evaluation**:
- **MAX wins**: More XOX triads than OXO triads
- **MIN wins**: More OXO triads than XOX triads  
- **Draw**: Equal counts of both triads, or no triads formed when board is full

### Triad Detection
Triads are detected in four directions:
- **Horizontal**: Left-to-right across rows
- **Vertical**: Top-to-bottom down columns
- **Diagonal**: Both main diagonal directions
  
## Game Flow

1. **Initialize**: Random non-adjacent placement of X and O
2. **Computer turn**: Minimax selects optimal move for MAX
3. **Human turn**: Player inputs move coordinates
4. **Evaluation**: Check for triads after each move
5. **Termination**: Game ends when triads form or board fills

## Example Terminal States

1. **MAX Victory**: Computer forms more XOX triads
2. **MIN Victory**: Player forms more OXO triads
3. **Draw (Equal triads)**: Same number of XOX and OXO patterns
4. **Draw (No triads)**: Board full without any triad formation

## Compilation and Usage

### Compile
```bash
gcc -o minmax minmax.c -lm
```

### Run
```bash
./minmax
```

### Sample Gameplay
```
Game starts! You are MIN (O), computer is MAX (X).

  0 1 2
0 _ X _ 
1 _ _ _ 
2 O _ _ 
3 _ _ _ 

Computer places X at (1, 1)

  0 1 2
0 _ X _ 
1 _ X _ 
2 O _ _ 
3 _ _ _ 

Enter your move (row column):

```

## Author

**Konstantinos Vardakas**  

---

*This implementation demonstrates classical AI game theory through the Minimax algorithm applied to a custom grid-based strategy game with unique victory conditions.*
