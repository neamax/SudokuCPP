#pragma once
#include <vector>
#include <string>

// Sudoku game class
class SudokuGame
{
public:
    SudokuGame(); // Constructor: initializes the board
    void play();  // Main game loop

private:
    std::vector<std::vector<int>> invalidEntries;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> solution;
    std::vector<std::vector<int>> fullSolution;
    std::vector<std::vector<bool>> userEntries; // track user-added numbers
    std::string lastMessage = "";               // store last message to show after screen clears
    bool lastMoveValid = false;
    void generatePuzzle();                                              // Generate a Sudoku puzzle
    void displayBoard();                                                // Print the current board
    bool isMoveValid(int row, int col, int num, bool checkAgainstClue); // Check if move is valid
    bool solve(std::vector<std::vector<int>> &b);                       // Recursive solver
    bool isSolved();                                                    // Check if board is fully filled
    void showIntro();
};
