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
    // Going to use this for manual debugging for the time being, until the actual main() gets made:

    // List the available boards:
    // filesystem::path workingDir = filesystem::current_path();
    
        // Take two steps out from the program's working directory, then navigate to the input files:
    filesystem::path sourceDir = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";
    
        // Make a list for the user to pick from:
    vector<filesystem::path> boardFiles;
    for (const auto& itr : filesystem::recursive_directory_iterator(sourceDir)) {
        boardFiles.push_back(itr);
    }

        // Select a file to create the working board object:
    cout << "Select starting board:" << endl;
    for (int i = 0; i < boardFiles.size(); i++) {
        cout << i+1 << ": " << boardFiles.at(i).filename() << endl;
    }
    cout << "0: Quit" << endl << endl;
    int userPick;
    cin >> userPick;
        // Sanitize input:
    userPick = (int)userPick - 1;
    if (userPick < 0 || userPick > boardFiles.size()) {
        return 0;
    }
        // Pick starting file:
    SudokuBoard* gameBoard = new SudokuBoard(boardFiles.at(userPick).string());
    gameBoard->printBoard();

    return 0;
}
