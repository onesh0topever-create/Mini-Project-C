#include <stdio.h>

// Phase 1: Set up the Board
// A 3x3 2D array initialized with characters '1' through '9'
char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Function prototypes
void printBoard();
int checkWin();
int checkDraw();

int main() {
    int player = 1;
    int choice;
    int row, col;
    char mark;
    int gameStatus = 0; // 0 = playing, 1 = win, -1 = draw

    // Phase 3: The Game Loop
    while (gameStatus == 0) {
        printBoard();
        
        // Alternate turns between Player 1 and Player 2
        player = (player % 2 != 0) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("Player %d, enter a number: ", player);
        scanf("%d", &choice);

        // Convert the user's choice (1-9) into 2D array indexes (row and col)
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        // Phase 4: Input Validation (The "Hacker" Check)
        // Check if input is between 1-9 AND the spot isn't already taken by X or O
        if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = mark; // Place the X or O
            
            // Phase 5: Check Win/Draw Condition
            if (checkWin() == 1) {
                gameStatus = 1; // Someone won
            } else if (checkDraw() == 1) {
                gameStatus = -1; // It's a tie
            } else {
                player++; // Move to the next player's turn
            }
        } else {
            printf("Invalid move! That spot is taken or doesn't exist. Press Enter to try again.\n");
            // Consume the newline character so the prompt doesn't loop infinitely on bad input
            while (getchar() != '\n'); 
            getchar();
        }
    }

    // End of game results
    printBoard();
    if (gameStatus == 1) {
        printf("==> \aPlayer %d wins! Congratulations!\n", player);
    } else {
        printf("==> \aGame is a draw!\n");
    }

    return 0;
}

// Phase 2: Draw the Grid
void printBoard() {
    // Clear screen command (works on most terminals)
    printf("\033[H\033[J"); 
    
    printf("\n\n\tTic Tac Toe\n\n");
    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n\n");
}

// Phase 5 Logic: Check all 8 possible win conditions
int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0; // No winner yet
}

// Phase 5 Logic: Check if all spaces are filled without a winner
int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0; // Found an empty spot (a number), not a draw yet
            }
        }
    }
    return 1; // All spots filled, it's a draw
}