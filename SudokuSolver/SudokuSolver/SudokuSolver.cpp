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
    /* Given a note at a board coordinate;
    if no other cells in that row share the note,
    or if no other cells in that column share the note, value can be written. */
    
    bool startNote = board->getCellNote(row, col, val);
    bool rowNote = false;
    bool colNote = false;

    if (startNote) {
        for (int r = 1; r <= board->getBoardSize(); r++) {
            if (r != row && board->getCellNote(r, col, val)) {
                rowNote = false;
            }
        }
        rowNote = true;
        for (int c = 1; c <= board->getBoardSize(); c++) {
            if (c != col && board->getCellNote(row, c, val)) {
                colNote = false;
            }
        }
        colNote = true;
    }

    return (rowNote || colNote);
}

bool onlyNoteVal(SudokuBoard* board, int row, int col, int val) {
    /* Given a note at a board cooredinate;
    if that note is the only note in the cell, the value can be written. */
    
    if (board->getCellNote(row, col, val)) {
        for (int n = 1; n <= board->getBoardSize(); n++) {
            if (board->getCellNote(row, col, n) && n != val) {
                return false;
            }
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
    Sudoku* gameState = NULL;
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
        gameState = new Sudoku(*currentBoard);
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
        while (!gameState->boardSolved() && passCount <= gameMax)
        {
            cout << "Solution pass #" << passCount + 1 << "..." << endl;
            
            // For each unsolved value...
            auto val = gameState->lowest();
            while (val != gameState->highest()) {
                if (val->second < currentBoard->getBoardSize()) {
                    
                    /*DEBUG*/
                    cout << "Testing " << val->first << ":" << endl;
                    /*DEBUG*/

                    // For each row...
                    for (int row = 1; row <= currentBoard->getBoardSize(); row++) {
                        // For each column...
                        for (int col = 1; col <= currentBoard->getBoardSize(); col++) {
                            // For empty cells...
                            if (currentBoard->getCellVal(row, col) == 0) {
                                // Write solutions for note-isolated values:
                                if (hangingNote(currentBoard, row, col, val->first)
                                    || onlyNoteVal(currentBoard, row, col, val->first)) {
                                    currentBoard->setCellVal(row, col, val->first);

                                    /*DEBUG*/
                                    //currentBoard->printBoard();
                                    gameState->printGameBoard();
                                    /*DEBUG*/

                                    // Remove notes:
                                    currentBoard->clearRowNotes(row, val->first);
                                    currentBoard->clearColNotes(col, val->first);
                                    currentBoard->clearBlockNotes(row, col, val->first);
                                }
                            }
                        }
                    }
                }
                // Go to next value...
                val++;
            }

            // Continue:
            passCount++;
            if (gameState->boardSolved()) {
                cout << "Solution found:" << endl;
                currentBoard->printBoard();
                cout << endl;
                delete currentBoard;
                delete gameState;
                continue;
            }
        }

        if (passCount >= gameMax) {
            cout << "Solution not found." << endl << endl;
            currentBoard->printBoard();
            cout << endl;
            delete currentBoard;
            delete gameState;
            continue;
        }

    } while (userPick != 0 || userPick > (int) boardFiles.size());

    return 0;
}