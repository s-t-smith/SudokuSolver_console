/*
* SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
* The program will make use of the Sudoku classes to create an NxN game board and input solutions until the board has all digits (1..N) in each row, column and block.
* The algorithm will follow these steps:
* - Eliminate possible solution notes in a block
* - Eliminate possible solution notes in a row
* - Eliminate possible solution notes in a column
* - Iterate through each row to find singular solution notes, write solutions where applicable
* - Iterate through each column to find singular solution notes, write solutions where applicable
* - Iterate through each block to find singular solution notes, write solutions where applicable
* - Continue until all cells have solutions written
*/

#include "Sudoku.h"
#include <iostream>
#include <filesystem>
using namespace std;

int main()
{
        // Take two steps out from the program's working directory, then navigate to the input files:
    filesystem::path sourceDir = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";
    
        // Make a list for the user to pick from:
    vector<filesystem::path> boardFiles;
    for (const auto& itr : filesystem::recursive_directory_iterator(sourceDir)) {
        boardFiles.push_back(itr);
    }

    int userPick = 0;
    int passCount = 0;
    Sudoku* currentGame = NULL;
    do {
        // List available files:
        cout << "Select starting board:" << endl;
        for (int i = 0; i < (int) boardFiles.size(); i++) {
            cout << i + 1 << ": " << boardFiles.at(i).filename() << endl;
        }
        cout << "0: Quit" << endl << endl;
        
        // Select a file to create the working board object:
        cin >> userPick;
        // Sanitize input:
        userPick = (int)userPick - 1;
        if (userPick < 0 || userPick > (int) boardFiles.size()) {
            break;
        }

        // Pick starting file:
        currentGame = new Sudoku(boardFiles.at(userPick).string()); // stringify the directory for the chosen starting board.
            // Maybe I should adjust the class to construct from a directory instead of a string.

        /*
        * IMPORTANT!
        * I should make a limit on the number of passes this loop can make before it gives up;
        *   don't want this thing just spinning off into infinity.
        * Idea: loop through each value and clear notes. If that doesn't create a singular option in a number of passes equal to the number of values, give up.
        */
        passCount = 0;
        while (!currentGame->checkGO() && passCount <= currentGame->getBoardSize())
        {
            currentGame->checkState();
            if (currentGame->checkGO()) {
                cout << "Solution found:" << endl;
                currentGame->printBoard();
                break;
            }
            
            // Check notes for singular values:

            // Write singular solutions:

            // Clear notes:

            // Continue:
            passCount++;
        }

        if (passCount >= currentGame->getBoardSize()) {
            cout << "Solution not found." << endl << endl;
        }

    } while (userPick < 0 || userPick > (int) boardFiles.size());

    return 0;
}