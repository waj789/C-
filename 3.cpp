#include <iostream>
#include <vector>

using namespace std;

// Define the size of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num) return false;
    }

    // Check the column
    for (int x = 0; x < N; ++x) {
        if (grid[x][col] == num) return false;
    }

    // Check the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) return false;
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using Backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if (grid[row][col] == 0) { // Empty cell found
                for (int num = 1; num <= 9; ++num) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = 0; // Backtrack
                    }
                }
                return false; // No valid number found, need to backtrack
            }
        }
    }
    return true; // Puzzle solved
}

int main() {
    // Define a Sudoku puzzle (0 denotes empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Initial Sudoku Puzzle:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku Puzzle:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}
