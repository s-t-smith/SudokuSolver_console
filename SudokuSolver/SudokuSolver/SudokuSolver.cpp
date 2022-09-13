/*
* SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
* The program will make use of the Sudoku classes to create a 9x9 game board and input solutions until the board has all digits (1..9) in each row, column and 3x3 block.
* The algorithm will follow these steps:
* - Eliminate possible solution notes in a row
* - Eliminate possible solution notes in a column
* - Eliminate possible solution notes in a block
* - Iterate through each row to find singular solution notes, write solutions where applicable
* - Iterate through each column to find singular solution notes, write solutions where applicable
* - Iterate through each block to find singular solution notes, write solutions where applicable
* - Continue until all cells have solutions written
*/

#include "SudokuCell.h"
#include "SudokuBoard.h"
#include "Sudoku.h"
#include <iostream>
using namespace std;

// Function declarations:
/*
* [put some explanations here]
*/
void clearRowNotes(int val, int row);
void clearColNotes(int val, int col);
void clearBlockNotes(int val, int blk);
bool isWrittenRow(int val, int row);
bool isWrittenCol(int val, int col);
bool isWrittenBlock(int val, int blk);
void placeSolution(int val, int row, int col);


// Main:
int main()
{
    cout << "Main program not yet written." << endl;
}


// Funciton definitions:
void clearRowNotes(int val, int row) {}

void clearColNotes(int val, int col) {}

void clearBlockNotes(int val, int blk) {}

bool isWrittenRow(int val, int row) {}

bool isWrittenCol(int val, int col) {}

bool isWrittenBlock(int val, int blk) {}

void placeSolution(int val, int row, int col) {}