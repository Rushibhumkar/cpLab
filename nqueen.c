#include <stdio.h>
#define N 8

int board[N][N] = {0};

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '-');
        }
        printf("\n");
    }
    printf("\n");
}

int isSafe(int row, int col) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++) {
        if (board[row][i]) {
            return 0;
        }
    }

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return 0;
        }
    }

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return 0;
        }
    }

    return 1;
}

int solveNQueens(int col) {
    if (col >= N) {
        // All queens are placed. Print the board.
        printBoard();
        return 1; // Return 1 to indicate a solution is found.
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            count += solveNQueens(col + 1);
            board[i][col] = 0; // Backtrack and remove the queen from this position.
        }
    }
    return count;
}

int main() {
    int totalSolutions = solveNQueens(0);
    printf("Total solutions: %d\n", totalSolutions);
    return 0;
}
