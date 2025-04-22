#include "SudokuGame.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

// Constructor
SudokuGame::SudokuGame()
{
    board = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    solution = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    fullSolution = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    userEntries = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));
    invalidEntries = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    generatePuzzle();
}

std::vector<int> getShuffledDigits()
{
    std::vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(digits.begin(), digits.end(), g);
    return digits;
}

void SudokuGame::generatePuzzle()
{
    solve(board);
    fullSolution = board; // full correct solution
    solution = board;     // start with all values

    int clues = 30;
    while (clues > 0)
    {
        int row = rand() % 9;
        int col = rand() % 9;
        if (solution[row][col] == 0)
            continue;
        solution[row][col] = 0;
        --clues;
    }

    board = solution; // final board for user to interact with
}

void SudokuGame::displayBoard()
{
    std::cout << "\n   ";
    for (int i = 0; i < 9; ++i)
        std::cout << "\033[36m" << i + 1 << " \033[0m"; // Cyan column numbers
    std::cout << "\n";
    for (int i = 0; i < 9; ++i)
    {
        std::cout << "\033[36m" << i + 1 << "\033[0m |"; // Cyan row numbers
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] != 0)
            {
                if (userEntries[i][j])
                    std::cout << "\033[32m" << board[i][j] << " \033[0m"; // Green
                else
                    std::cout << board[i][j] << " "; // Default colour for clues
            }
            else if (invalidEntries[i][j] != 0)
            {
                std::cout << "\033[31m" << invalidEntries[i][j] << " \033[0m"; // Red
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
    if (!lastMessage.empty())
    {
        std::cout << "\n\033[33m" << lastMessage << "\033[0m\n"; // Yellow last message
    }
}

bool SudokuGame::isMoveValid(int row, int col, int num, bool checkAgainstClue)
{
    if (checkAgainstClue && solution[row][col] != 0)
        return false;

    for (int i = 0; i < 9; ++i)
    {
        if (board[row][i] == num || board[i][col] == num)
            return false;
        int r = 3 * (row / 3) + i / 3;
        int c = 3 * (col / 3) + i % 3;
        if (board[r][c] == num)
            return false;
    }
    return true;
}

bool SudokuGame::solve(std::vector<std::vector<int>> &b)
{
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (b[row][col] == 0)
            {
                std::vector<int> digits = getShuffledDigits();
                for (int num : digits)
                {
                    if (isMoveValid(row, col, num, false))
                    {
                        b[row][col] = num;
                        if (solve(b))
                            return true;
                        b[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool SudokuGame::isSolved()
{
    for (const auto &row : board)
        for (int val : row)
            if (val == 0)
                return false;
    return true;
}

void SudokuGame::showIntro()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif

    std::cout << "\033[36m======================================\n";
    std::cout << "\033[36m==            Welcome to            ==\n";
    std::cout << "\033[36m==       THE SUDOKU CHALLENGE       ==\n";
    std::cout << "\033[36m==              v0.0.1              ==\n";
    std::cout << "\033[36m==                                  ==\n";
    std::cout << "\033[36m==     Developed by Neama Kazemi    ==\n";
    std::cout << "\033[36m==           Github/neamax          ==\n";
    std::cout << "\033[36m==                                  ==\n";
    std::cout << "\033[36m==      LuckyGene Indie Studios     ==\n";
    std::cout << "\033[36m==         www.luckygene.net        ==\n";
    std::cout << "\033[36m======================================\033[0m\n";
    std::cout << "\n\033[36m1. Start Game\n2. Exit\033[0m\n";
    std::cout << "\nChoose an option: ";

    int choice;
    std::cin >> choice;
    if (choice != 1)
    {
        std::cout << "\nGoodbye!\n";
        exit(0);
    }
}

void SudokuGame::play()
{
    showIntro();
    int row, col, num;

    while (!isSolved())
    {
        system("cls"); // or system("clear")
        displayBoard();

        std::cout << "\n\033[90mEnter your move (row col number): \033[0m"; // Grey input prompt
        std::cin >> row >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9)
        {
            lastMessage = "Invalid input. Try again.";
            continue;
        }

        if (solution[row - 1][col - 1] != 0)
        {
            lastMessage = "Can't change original clue.";
            continue;
        }

        if (isMoveValid(row - 1, col - 1, num, true))
        {
            board[row - 1][col - 1] = num;
            userEntries[row - 1][col - 1] = true;
            invalidEntries[row - 1][col - 1] = 0; // Clear any past mistake
            lastMessage = "Move accepted.";
            lastMoveValid = true;
        }
        else
        {
            if (board[row - 1][col - 1] == 0) // It's an empty spot, just wrong number
                invalidEntries[row - 1][col - 1] = num;

            lastMessage = "Invalid move.";
            lastMoveValid = false;
        }
    }

    system("cls");
    displayBoard();
    std::cout << "\n\033[92mCongratulations! You solved the puzzle.\033[0m\n";
}
