#include "SudokuGame.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

// Constructor: Initialises an empty board and solution, then generates a puzzle
SudokuGame::SudokuGame() {
    board = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    solution = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    generatePuzzle();
}

// Generate a complete Sudoku board and remove numbers to create a playable puzzle
void SudokuGame::generatePuzzle() {
    srand(static_cast<unsigned int>(time(0)));
    solve(board);         // Fill board with a valid solution
    solution = board;     // Store solution for clue-checking

    int clues = 30;       // Number of visible clues left on board
    while (clues > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] == 0) continue;
        board[row][col] = 0;
        --clues;
    }
}

// Display the current board to console
void SudokuGame::displayBoard() {
    std::cout << "\n   ";
    for (int i = 0; i < 9; ++i) std::cout << i + 1 << " ";
    std::cout << "\n";
    for (int i = 0; i < 9; ++i) {
        std::cout << i + 1 << " |";
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) std::cout << "  ";
            else std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Validates a move. If checkAgainstClue is true, it prevents changing original puzzle clues
bool SudokuGame::isMoveValid(int row, int col, int num, bool checkAgainstClue) {
    if (checkAgainstClue && solution[row][col] != 0) return false;

    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num) return false;
        int r = 3 * (row / 3) + i / 3;
        int c = 3 * (col / 3) + i % 3;
        if (board[r][c] == num) return false;
    }
    return true;
}

// Recursive backtracking solver used to fill the board with a valid complete solution
bool SudokuGame::solve(std::vector<std::vector<int>>& b) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (b[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isMoveValid(row, col, num, false)) {
                        b[row][col] = num;
                        if (solve(b)) return true;
                        b[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Check if the board is completely filled
bool SudokuGame::isSolved() {
    for (const auto& row : board)
        for (int val : row)
            if (val == 0) return false;
    return true;
}

// Main game loop — keeps prompting user until board is complete
void SudokuGame::play() {
    int row, col, num;
    while (!isSolved()) {
        displayBoard();
        std::cout << "\nEnter your move (row col number): ";
        std::cin >> row >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (solution[row - 1][col - 1] != 0) {
            std::cout << "Can't change original clue.\n";
            continue;
        }

        if (isMoveValid(row - 1, col - 1, num, true)) {
            board[row - 1][col - 1] = num;
        } else {
            std::cout << "Invalid move.\n";
        }
    }

    displayBoard();
    std::cout << "Congratulations! You solved the puzzle.\n";
}