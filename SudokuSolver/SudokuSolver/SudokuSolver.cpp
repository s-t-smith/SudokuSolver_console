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
#include "SudokuBoard.h"
#include <iostream>
#include <filesystem>
using namespace std;

//bool intersectionCheck(Sudoku* game, int row, int col, int val) {
//    bool rowCheck = !game->rowValCheck(row, val);
//    bool colCheck = !game->colValCheck(col, val);
//    bool blkCheck = !game->blockValCheck(row, col, val);
//
//    // Intersection is available if and only if all three checks return 'value not present':
//    return (rowCheck && colCheck && blkCheck);
//}

bool hangingNote(SudokuBoard* board, int row, int col, int val) {
    // TODO: finish this.
    return false;   // placeholder
}

bool onlyNoteVal(SudokuBoard* board, int row, int col, int val) {
    if (!board->getCellNote(row, col, val)) {
        return false;
    }
    int noteCheck = val;
    for (int n = 1; n <= board->getBoardSize(); n++) {
        if (board->getCellNote(row, col, n) && n != noteCheck) {
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
    SudokuBoard* currentBoard = NULL;
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
        currentBoard = new SudokuBoard(boardFiles.at(userPick).string()); // stringify the directory for the chosen starting board.
            // Maybe I should adjust the class to construct from a directory instead of a string.
        cout << "Starting board:" << endl;
        currentBoard->printBoard();
        cout << endl;
        gameMax = currentBoard->getBoardSize();

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
                    int cellVal = currentBoard->getCellVal(row, col);
                    if (cellVal != 0) {
                        currentBoard->clearRowNotes(row, cellVal);
                        currentBoard->clearColNotes(col, cellVal);
                        currentBoard->clearBlockNotes(row, col, cellVal);
                    }
                }
            }

            // Write solutions:
            // Check each row:
            for (int row = 1; row <= gameMax; row++) {
                // Check each column:
                for (int col = 1; col <= gameMax; col++) {
                    
                    // When a cell is empty:
                    if (currentBoard->getCellVal(row, col) == 0) {
                        for (int n = 1; n <= gameMax; n++) {
                            // Check each value note, write solution when a single note is found:
                            if (currentBoard->getCellNote(row, col, n)) {
                                if (onlyNoteVal(currentBoard, row, col, n)
                                    || hangingNote(currentBoard, row, col, n)) {
                                    continue;
                                }
                            }
                        }

                        // Debugging:
                        /*printf("(%i, %i) Val: %i \n", row, col, currentBoard->getBoardCellVal(row, col));
                        cout << "Notes: (";
                        for (int n = 1; n <= gameMax; n++) {
                            if (currentBoard->getBoardCellNote(row, col, n)) {
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
                currentBoard->printBoard();
                cout << endl;
                break;
            }
        }

        if (passCount >= gameMax) {
            cout << "Solution not found." << endl << endl;
            currentBoard->printBoard();
            cout << endl;
        }

    } while (userPick != 0 || userPick > (int) boardFiles.size());

    return 0;
}