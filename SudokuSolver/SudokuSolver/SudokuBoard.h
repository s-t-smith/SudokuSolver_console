#pragma once

#include "SudokuCell.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*
* This class will define the game space for a session of Sudoku.
*/

class SudokuBoard
{
	// To expose functions to the upper-layer class:
	friend class Sudoku;

public:
	/* CONSTRUCTORS:
	* SudokuBoard(int size)-
	*	creates a blank board, square in the given size.
	* SudokuBoard(string filename)-
	*	creates a board with the values specified in the input file.
	* initBoard(int max)-
	*	sets private member variables based on the maximum solution value.
	*/
	SudokuBoard();
	SudokuBoard(int size);
	SudokuBoard(string fileName);
	~SudokuBoard();
	void initBoard(int max);

	/* BOARD FUNCTIONS:
	* getBoardSize()-
	*	returns the length of a board side, which coincides with the maximum solution value.
	* getBlockSize()-
	*	returns the length of a side of a subarray of the board; for a 9x9 board, returns 3.
	* setCellVall(int row, int col, val)-
	*	writes a given value to the cell at board coordinates [row, col].
	* getCellVal(int row, int col)-
	*	returns the value written to a cell at board coordinates [row, col].
	* setCellNote(int row, int col, int index, bool set)-
	*	sets or clears a note on a cell at board coordinates [row, col].
	* getCellNote(int row, int col, int index)-
	*	returns the note list item from a cell at board coordinates [row, col].
	* printBoard()-
	*	displays the array of cells on the board; only shows written values, not notes.
	*/
	int getBoardSize();
	int getBlockSize();
	void setCellVal(int row, int col, int val);
	int getCellVal(int row, int col);
	void setCellNote(int row, int col, int index, bool set);
	bool getCellNote(int row, int col, int index);
	void printBoard();

	/* NOTE AND VALUE FUNCTIONS:
	* rowValCheck(int row, int val)-
	*	checks all cells in a given row, returns true if any one of those cells has the given value written.
	* clearRowNotes(int row, int val)-
	*	removes a given value from the note lists of all cells in a given row.
	* colValCheck(int col, int val)-
	*	checks all cells in a given column, renturns true if any one of those cells has the given value written.
	* clearColNotes(int col, int val)-
	*	removes a given value from the note lists of all cells in a given column.
	* blockCoord(int row, int col)-
	*	returns a single integer representation of a subarrya from a given set of coordinates; subarrays can be thought of as numbered on the same series as solution values, left-to-right then top-to-bottom.
	* blockRef(int blk)-
	*	sets the private fields for dereferencing subarrays from a given subarray index.
	* blockValCheck(int blk, int val)-
	*	checks all cells in a given subarray, returns true if any one of those cells has the given value written.
	* blockValCheck(int row, int col, int val)-
	*	checks all cells in a given subarray, returns true if any one of those cells has the given value written; uses board coordinates instead of subarray index.
	* clearBlockNotes(int blk, int val)-
	*	removes a given value from the note lists of all cells in a given subarray. 
	* clearBlockNotes(int row, int col, int val)-
	*	removes a given value from the note lists of all cells in a given subarray; uses board coordinates instead of subarray index.
	*/
	bool rowValCheck(int row, int val);
	void clearRowNotes(int row, int val);
	bool colValCheck(int col, int val);
	void clearColNotes(int col, int val);
	int blockCoord(int row, int col);
	void blockRef(int blk);
	bool blockValCheck(int blk, int val);
	bool blockValCheck(int row, int col, int val);
	void clearBlockNotes(int blk, int val);
	void clearBlockNotes(int row, int col, int val);

private:
	/* Board info fields: */
	int boardSize;
	int blockSize;
	/* Board reference points: */
	int blockRowStart;
	int blockColStart;
	int blockRowEnd;
	int blockColEnd;
	/* Board: */
	vector<vector<SudokuCell*>> board;
};


SudokuBoard::SudokuBoard() {
	initBoard(9);
}

SudokuBoard::SudokuBoard(int size) {
	// Create a square array of <size>:
	double checkSR = sqrt(size);
	if (ceil(checkSR) == floor(checkSR)) {
		initBoard(size);
	}
	else {
		// If the given size isn't a perfect square, default to a 9x9 board:
		initBoard(9);
	}
	// Bonus: This could be expanded to adjust to the closest size other than 9x9.
}

SudokuBoard::SudokuBoard(string fileName) : SudokuBoard(9){
	int inputSize, inputRow, inputCol, inputVal;
	ifstream inputFile;
	inputFile.open(fileName);
	if (inputFile.is_open()) {
		// First character should be the board size/max value:
		inputFile >> inputSize;
		// Create empty board:
		double checkSR = sqrt(inputSize);
		if (ceil(checkSR) == floor(checkSR)) {
			initBoard(inputSize);
			// Populate cell values:
			while (!inputFile.eof()) {
				inputFile >> inputRow;
				inputFile >> inputCol;
				inputFile >> inputVal;
				setCellVal(inputRow, inputCol, inputVal);
			}
		}
		inputFile.close();
	}
	else {
		// If the file fails, create an empty 9x9:
		initBoard(9);
	}
}

SudokuBoard::~SudokuBoard() {
	// Clear memory from board:
	for (auto r : board) {
		for (auto c : r) {
			delete c;
		}
	}
}

// Constructor helper:
void SudokuBoard::initBoard(int max) {
	// No workie:
	/*for (auto i : board) {
		i.resize(boardSize);
		for (auto j : i) {
			j = new SudokuCell();
		}
	}*/

	// Set private fields:
	boardSize = max;
	blockSize = (int)sqrt(max);

	// Create cell array:
	board.resize(boardSize);
	for (int i = 0; i < boardSize; i++) {
		board[i].resize(boardSize);
		for (int j = 0; j < max; j++) {
			board[i][j] = new SudokuCell(0, boardSize);
		}
	}
}

int SudokuBoard::getBoardSize() {
	// Returns the board's maximum value/row size:
	return boardSize;
}

int SudokuBoard::getBlockSize() {
	// Return the size of a block on the board:
	return blockSize;
}

void SudokuBoard::setCellVal(int row, int col, int val) {
	// Inputs are assumed to be 1-ref, cell arrays are 0-ref:
	board[row - 1][col - 1]->setVal(val);
}

int SudokuBoard::getCellVal(int row, int col) {
	// Inputs are assumed to be 1-ref, cell arrays are 0-ref:
	return board[row - 1][col - 1]->getVal();
}

void SudokuBoard::setCellNote(int row, int col, int index, bool set) {
	// Inputs are assumed to be 1-ref, cell arrays are 0-ref:
	board[row - 1][col - 1]->setNote(index - 1, set);
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	// Inputs are assumed to be 1-ref, cell arrays are 0-ref:
	return board[row - 1][col - 1]->getNote(index - 1);
}

void SudokuBoard::printBoard() {
	for (int row = 1; row <= boardSize; row++) {
		for (int col = 1; col <= boardSize; col++) {
			cout << getCellVal(row, col);
			if ((col != boardSize) && (col % blockSize == 0)) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		if ((row != boardSize) && (row % blockSize == 0)) {
			cout << endl;
			for (int spc = 0; spc < 2*boardSize-1; spc++) {
				cout << "-";
			}
		}
		cout << endl;
	}
}

bool SudokuBoard::rowValCheck(int row, int val)
{
	// Returns true when a value is written to a board cell in a given row.
	/*for (int col = 1; col <= boardSize; col++) {
		if (getCellVal(row, col) == val) {
			return true;
		}
	}*/
	for (auto c : board[row - 1]) {
		if (c->getVal() == val) {
			return true;
		}
	}
	return false;
}

void SudokuBoard::clearRowNotes(int row, int val)
{
	for (auto c : board[row - 1]) {
		c->setNote(val - 1, false);
	}
	/*for (int col = 1; col <= boardSize; col++) {
		setCellNote(row, col, val, false);
	}*/
}

bool SudokuBoard::colValCheck(int col, int val)
{
	// Returns true when a value is written to a board cell in a given column.
	for (int row = 1; row <= boardSize; row++) {
		if (board[row - 1][col - 1]->getVal() == val) {
			return true;
		}
	}	// should try to streamline this like the row method.
	return false;
}

void SudokuBoard::clearColNotes(int col, int val)
{
	for (int row = 1; row <= boardSize; row++) {
		board[row - 1][col - 1]->setNote(val - 1, false);
	}
}

int SudokuBoard::blockCoord(int row, int col) {
	// Given a set of coordinates, set the cell index limits for looping functions.
	int blockRowRef = (int)((row - 1) / blockSize) * blockSize;	// for 9x9, this recontextualizes the row as 0, 3 or 6.
	int blockColRef = (int)((col - 1) / blockSize) + 1;	// for 9x9, this recontextualizes the col as 1, 2 or 3.
	return blockRowRef + blockColRef;
}

void SudokuBoard::blockRef(int blk) {
	// Given a single block number, set the cell index limits for looping functions.
	blockRowStart = (((int)(blk - 1) / blockSize) * blockSize) + 1;
	blockRowEnd = blockRowStart + blockSize;
	blockColStart = (((blk - 1) % blockSize) * blockSize) + 1;
	blockColEnd = blockColStart + blockSize;
}

bool SudokuBoard::blockValCheck(int blk, int val)
{
	blockRef(blk);
	for (int r = blockRowStart; r < blockRowEnd; r++) {
		for (int c = blockColStart; c < blockColEnd; c++) {
			if (board[r - 1][c - 1]->getVal() == val) {
				return true;
			}
		}
	}
	return false;
}

bool SudokuBoard::blockValCheck(int row, int col, int val)
{
	return blockValCheck(blockCoord(row, col), val);
}

void SudokuBoard::clearBlockNotes(int blk, int val)
{
	blockRef(blk);
	for (int r = blockRowStart; r < blockRowEnd; r++) {
		for (int c = blockColStart; c < blockColEnd; c++) {
			board[r - 1][c - 1]->setNote(val - 1, false);
		}
	}
}

void SudokuBoard::clearBlockNotes(int row, int col, int val)
{
	clearBlockNotes(blockCoord(row, col), val);
}