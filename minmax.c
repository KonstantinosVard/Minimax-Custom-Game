// Name: Konstantinos Vardakas 
// AM: 522

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ROWS 4
#define COLS 3

char board[ROWS][COLS];


float is_adjacent(int x1, int y1, int x2, int y2) {
    return fmax(abs(x1 - x2), abs(y1 - y2)) == 1;
}

// Initialize board with one X and one O in random non-adjacent positions
void init_board() {
    // Seed the random number generator
    srand(time(NULL));
    
    // Clear the board
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = '_';
    
    // Place X randomly
    int x_row = rand() % ROWS; // Random row: 0 to 3
    int x_col = rand() % COLS; // Random col: 0 to 2
    board[x_row][x_col] = 'X';
    
    // Place O in a random non-adjacent position
    int o_row, o_col;
    do {
        o_row = rand() % ROWS;
        o_col = rand() % COLS;
    } while (board[o_row][o_col] != '_' || is_adjacent(x_row, x_col, o_row, o_col));
    
    board[o_row][o_col] = 'O';
}

// Print board
void print_board() {
    printf("\n  0 1 2\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}


// Check for triad (XOX or OXO) in a sequence of three cells
int check_triad(char c1, char c2, char c3) {
    if (c1 == 'X' && c2 == 'O' && c3 == 'X')
        return 1; // XOX: Counts as one for MAX
    if (c1 == 'O' && c2 == 'X' && c3 == 'O')
        return -1; // OXO: Counts as one for MIN
    return 0;
}

// Check if board is full
int is_board_full() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (board[i][j] == '_')
                return 0;
    return 1;
}

// Check if game is over and determine winner by counting triads
int is_game_over(int *xox_count, int *oxo_count) {
    *xox_count = 0; // Count of XOX (MAX)
    *oxo_count = 0; // Count of OXO (MIN)
    int has_triad = 0; // Flag to indicate if any triad is found

    // Horizontal triads
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j <= COLS - 3; j++) {
            int result = check_triad(board[i][j], board[i][j+1], board[i][j+2]);
            if (result == 1) {
                (*xox_count)++;
                has_triad = 1;
            } else if (result == -1) {
                (*oxo_count)++;
                has_triad = 1;
            }
        }

    // Vertical triads
    for (int j = 0; j < COLS; j++)
        for (int i = 0; i <= ROWS - 3; i++) {
            int result = check_triad(board[i][j], board[i+1][j], board[i+2][j]);
            if (result == 1) {
                (*xox_count)++;
                has_triad = 1;
            } else if (result == -1) {
                (*oxo_count)++;
                has_triad = 1;
            }
        }

    // Diagonal triads (top-left to bottom-right)
    for (int i = 0; i <= ROWS - 3; i++)
        for (int j = 0; j <= COLS - 3; j++) {
            int result = check_triad(board[i][j], board[i+1][j+1], board[i+2][j+2]);
            if (result == 1) {
                (*xox_count)++;
                has_triad = 1;
            } else if (result == -1) {
                (*oxo_count)++;
                has_triad = 1;
            }
        }

    // Diagonal triads (bottom-left to top-right)
    for (int i = 2; i < ROWS; i++)
        for (int j = 0; j <= COLS - 3; j++) {
            int result = check_triad(board[i][j], board[i-1][j+1], board[i-2][j+2]);
            if (result == 1) {
                (*xox_count)++;
                has_triad = 1;
            } else if (result == -1) {
                (*oxo_count)++;
                has_triad = 1;
            }
        }

    // Determine outcome
    if (has_triad) {
        if (*xox_count > *oxo_count)
            return 1; // MAX wins
        if (*oxo_count > *xox_count)
            return -1; // MIN wins
        return 2; // Equal counts, draw
    }

    // No triads, check for draw
    if (is_board_full())
        return 2; // Draw
    return 0; // Game continues
}


// Minimax algorithm
int minimax(int is_max) {
    int xox_count, oxo_count; // Dummy variables for is_game_over
    int result = is_game_over(&xox_count, &oxo_count);
    if (result == 1)
        return 10; // MAX wins
    if (result == -1)
        return -10; // MIN wins
    if (result == 2)
        return 0; // Draw

    if (is_max) {
        int best_score = -1000;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    int score = minimax(0);
                    board[i][j] = '_';
                    if (score > best_score)
                        best_score = score;
                }
        return best_score;
    } else {
        int best_score = 1000;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    int score = minimax(1);
                    board[i][j] = '_';
                    if (score < best_score)
                        best_score = score;
                }
        return best_score;
    }
}

// Computer move (MAX)
void computer_move() {
    int best_score = -1000;
    int best_i = -1, best_j = -1;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (board[i][j] == '_') {
                board[i][j] = 'X';
                int score = minimax(0);
                board[i][j] = '_';
                if (score > best_score) {
                    best_score = score;
                    best_i = i;
                    best_j = j;
                }
            }
    board[best_i][best_j] = 'X';
    printf("Computer places X at (%d, %d)\n", best_i, best_j);
}

// Computer move (MIN)

// function to replace the user_move and play max vs min
// not used for the excercise, used to get example outputs in report

// void min_computer_move() {
//     int best_score = 1000; // Initialize to high value for minimization
//     int best_i = -1, best_j = -1;
//     for (int i = 0; i < ROWS; i++)
//         for (int j = 0; j < COLS; j++)
//             if (board[i][j] == '_') {
//                 board[i][j] = 'O';
//                 int score = minimax(1); // Next turn is MAX
//                 board[i][j] = '_';
//                 if (score < best_score) { // Minimize score for MIN
//                     best_score = score;
//                     best_i = i;
//                     best_j = j;
//                 }
//             }
//     board[best_i][best_j] = 'O';
//     printf("Player places O at (%d, %d)\n", best_i, best_j);
// }

// User move (MIN)
int user_move() {
    int i, j;
    while (1) {
        printf("Enter your move (row column): ");
        if (scanf("%d %d", &i, &j) != 2 || i < 0 || i >= ROWS || j < 0 || j >= COLS || board[i][j] != '_') {
            printf("Invalid move! Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            board[i][j] = 'O';
            break;
        }
    }
    return 1;
}

int main() {
    init_board();
    printf("Game starts! You are MIN (O), computer is MAX (X).\n");
    print_board();

    while (1) {
        // MAX's turn (computer)
        computer_move();
        print_board();
        int xox_count, oxo_count;
        int result = is_game_over(&xox_count, &oxo_count);
        if (result == 1) {
            printf("%d XOX counts (MAX) vs %d OXO counts (MIN)\n", xox_count, oxo_count);
            printf("Computer (MAX) wins!\n");
            break;
        }
        if (result == 2) {
            printf("%d XOX counts (MAX) vs %d OXO counts (MIN)\n", xox_count, oxo_count);
            printf("It's a draw!\n");
            break;
        }

        // MIN's turn (user)
        user_move();
        print_board();
        
        result = is_game_over(&xox_count, &oxo_count);
        if (result == -1) {
            printf("%d XOX counts (MAX) vs %d OXO counts (MIN)\n", xox_count, oxo_count);
            printf("You (MIN) win!\n");
            break;
        }
        if (result == 2) {
            printf("%d XOX counts (MAX) vs %d OXO counts (MIN)\n", xox_count, oxo_count);
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}