#pragma once
#include <vector>

// Sudoku game class
class SudokuGame {
public:
    SudokuGame();        // Constructor: initializes the board
    void play();         // Main game loop

private:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> solution;

    void generatePuzzle();                 // Generate a Sudoku puzzle
    void displayBoard();                   // Print the current board
    bool isMoveValid(int row, int col, int num); // Check if move is valid
    bool solve(std::vector<std::vector<int>>& b); // Recursive solver
    bool isSolved();                       // Check if board is fully filled
};