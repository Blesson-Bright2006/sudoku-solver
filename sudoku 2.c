
#include <stdio.h>

int puzzle[9][9] = {
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0},
};

void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int value);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main() {
    printf("Sudoku Solver\n");
    printf("Original Puzzle:\n");
    print_puzzle(puzzle);

    if (solve_puzzle(puzzle, 0, 0)) {
        printf("\nSolved Puzzle:\n");
        print_puzzle(puzzle);
    } else {
        printf("\nError: No solution found.\n");
    }
}

void print_puzzle(int puzzle[9][9]) {
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            printf("\n+------+------+------+");
        }
        printf("\n|");
        for (int col = 0; col < 9; col++) {
            printf("%d ", puzzle[row][col]);
            if ((col + 1) % 3 == 0) {
                printf("|");
            }
        }
    }
    printf("\n+------+------+------+\n");
}

int valid_move(int puzzle[9][9], int row, int col, int val) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == val) return 0;  // check row
        if (puzzle[i][col] == val) return 0;  // check col
    }

    int r = row - row % 3;
    int c = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[r+i][c+j] == val) return 0;  // check 3x3 box
        }
    }
    return 1;
}

int solve_puzzle(int puzzle[9][9], int row, int col) {
    if (col == 9) {  // move to next row
        if (row == 8) return 1;  // puzzle complete
        row++;
        col = 0;
    }

    if (puzzle[row][col] > 0) {  // skip filled cells
        return solve_puzzle(puzzle, row, col + 1);
    }

    for (int i = 1; i <= 9; i++) {
        if (valid_move(puzzle, row, col, i)) {
            puzzle[row][col] = i;
            if (solve_puzzle(puzzle, row, col + 1)) {
                return 1;
            }
            puzzle[row][col] = 0;  // backtrack
        }
    }
    return 0;  // no valid number found
}
+