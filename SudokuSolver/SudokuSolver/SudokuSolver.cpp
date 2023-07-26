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

bool intersectionCheck(Sudoku* game, int row, int col, int val) {
    bool rowCheck = !game->rowValCheck(row, val);
    bool colCheck = !game->colValCheck(col, val);
    bool blkCheck = !game->blockValCheck(row, col, val);

    // Intersection is available if and only if all three checks return 'value not present':
    return (rowCheck && colCheck && blkCheck);
}

bool onlyNote(Sudoku* game, int row, int col, int val) {
    if (!game->getBoardCellNote(row, col, val)) {
        return false;
    }
    int noteCheck = val;
    for (int n = 1; n <= game->getBoardSize(); n++) {
        if (game->getBoardCellNote(row, col, n) && n != noteCheck) {
            return false;
        }
    }
    return true;
}

int main()
{
        // Take two steps out from the program's working directory, then navigate to the input files:
    filesystem::path sourceDir = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";
    
        // Make a list for the user to pick from:
    vector<filesystem::path> boardFiles;
    for (const auto& itr : filesystem::recursive_directory_iterator(sourceDir)) {
        boardFiles.push_back(itr);
    }

    int gameMax = 0;
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
        if (userPick == 0) {
            break;
        }
        // Sanitize input:
        if (userPick != 0) {
            userPick = (int)userPick - 1;
            if (userPick < 0 || userPick >(int) boardFiles.size()) {
                break;
            }
        }
        
        // Pick starting file:
        currentGame = new Sudoku(boardFiles.at(userPick).string()); // stringify the directory for the chosen starting board.
            // Maybe I should adjust the class to construct from a directory instead of a string.
        cout << "Starting board:" << endl;
        currentGame->printGameBoard();
        cout << endl;
        gameMax = currentGame->getBoardSize();

        /*
        * IMPORTANT!
        * I should make a limit on the number of passes this loop can make before it gives up;
        *   don't want this thing just spinning off into infinity.
        * Idea: loop through each value and clear notes. If that doesn't create a singular option in a number of passes equal to the number of values, give up.
        */
        passCount = 0;
        while (!currentGame->boardSolved() && passCount <= gameMax)
        {
            cout << "Solution pass #" << passCount + 1 << "..." << endl;
            
            // Clear notes:
            // Check each row:
            for (int row = 1; row <= gameMax; row++) {
                // Check each column:
                for (int col = 1; col <= gameMax; col++) {
                    int cellVal = currentGame->getBoardCellVal(row, col);
                    if (cellVal != 0) {
                        currentGame->clearRowNotes(row, cellVal);
                        currentGame->clearColNotes(col, cellVal);
                        currentGame->clearBlockNotes(row, col, cellVal);
                    }
                }
            }

            // Write solutions:
            // Check each row:
            for (int row = 1; row <= gameMax; row++) {
                // Check each column:
                for (int col = 1; col <= gameMax; col++) {
                    
                    // When a cell is empty:
                    if (currentGame->getBoardCellVal(row, col) == 0) {
                        for (int n = 1; n <= gameMax; n++) {
                            // Check each value note, write solution when a single note is found:
                            if (onlyNote(currentGame, row, col, n)) {
                                currentGame->setBoardCellVal(row, col, n);
                                continue;
                            }

                            // TODO: validate this algorithm step:
                            if (intersectionCheck(currentGame, row, col, n)) {
                                currentGame->setBoardCellVal(row, col, n);
                                continue;
                            }
                        }

                        // Debugging:
                        /*printf("(%i, %i) Val: %i \n", row, col, currentGame->getBoardCellVal(row, col));
                        cout << "Notes: (";
                        for (int n = 1; n <= gameMax; n++) {
                            if (currentGame->getBoardCellNote(row, col, n)) {
                                cout << n << " ";
                            }
                        }
                        cout << ")" << endl;*/
                    }
                }
            }
            // Continue:
            passCount++;
            if (currentGame->boardSolved()) {
                cout << "Solution found:" << endl;
                currentGame->printGameBoard();
                cout << endl;
                break;
            }
        }

        if (passCount >= gameMax) {
            cout << "Solution not found." << endl << endl;
            currentGame->printGameBoard();
            cout << endl;
        }

    } while (userPick != 0 || userPick > (int) boardFiles.size());

    return 0;
}