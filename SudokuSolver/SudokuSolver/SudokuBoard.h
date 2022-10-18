#pragma once

#include "SudokuBlock.h"
#include <string>
#include <iostream>

using namespace std;

/*
* This class will define the game space for a session of Sudoku.
* It will keep track of a 9x9 set of SudokuCell objects and pass user function calls down to those objects.
*/

class SudokuBoard
{
	/*
	* Public functions:
	* SudokuBoard() - Default constructor; makes an empty board object with no values written to any cells.
	* ~SudokuBoard() - Default desctructor - might not have much use for this.
	* setCellVal - writes a solution to a cell by way of the underlying object's function.
	* getCellVal - returns a solution written in a cell by way of the underlying object's function.
	* setCellNote - sets the 'index' note on a cell to true, uses the underlying object's function.
	* clearCellNote - sets the 'index' note on a cell to false, uses the underlyiing object's function.
	* getCellNote - returns the state of the underlying object's 'index' note.
	* printBoard - outputs the board in a 9x9 format to the console.
	*/
public:
	SudokuBoard();
	~SudokuBoard();
	void setCellVal(int row, int col, int val);
	int getCellVal(int row, int col);
	void setCellNote(int row, int col, int index);
	void clearCellNote(int row, int col, int index);
	bool getCellNote(int row, int col, int index);
	void printBoard();

	/*
	* Private members:
	* board - a 9x9 array of SudokuCell objects.
	*	- In a later implementation, this could be adjusted for scalability and/or additional dimensions.
	* solutionProgress - keeps track of how many solutions exist on the board; a complete board will have 9 of each digit.
	*/
private:
	SudokuBlock* board[3][3];
		// If I change to vectors, this could scale better, and I could use iterators, which might be handy for blocks.
};


SudokuBoard::SudokuBoard() {
	// Creates a 9x9 set of empty SudokuCell objects.
	for (int r = 0; r < 3; r++) {	
		// Create empty cells:
		for (int c = 0; c < 3; c++) {
			board[r][c] = new SudokuBlock();
		}
	}
}

SudokuBoard::~SudokuBoard() {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			delete board[r][c];
		}
	}
}

void SudokuBoard::setCellVal(int row, int col, int val) {
	board[row / 3][col / 3]->setBlockCellVal(row % 3, col % 3, val);
}

int SudokuBoard::getCellVal(int row, int col) {
	return board[row / 3][col / 3]->getBlockCellVal(row % 3, col % 3);
}

void SudokuBoard::setCellNote(int row, int col, int index) {
	board[row / 3][col / 3]->setBlockCellNote(row % 3, col % 3, index);
}

void SudokuBoard::clearCellNote(int row, int col, int index) {
	board[row / 3][col / 3]->clearBlockCellNote(row % 3, col % 3, index);
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	return board[row / 3][col / 3]->getBlockCellNote(row % 3, col % 3, index);
}

void SudokuBoard::printBoard() {
	int cellVal = 0;
	cout << endl;
	cout << "Current board:" << endl;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			cout << getCellVal(row, col);
		}
		cout << endl;
	}
	cout << endl;
}