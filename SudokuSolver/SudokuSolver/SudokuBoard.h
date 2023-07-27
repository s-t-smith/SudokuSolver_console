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
	/*
	* Public functions:
	* SudokuBoard(int size) - Explicit constructor; makes an empty board with a user-provider number of rows and columns.
	* SudokuBoard(string fileName) - Explicit consturctor; makes a board using a text file to populate cell values.
	* ~SudokuBoard() - Default desctructor; frees pointer memory from cell objects.
	* getBoardSize() - returns the row/column/max value for the board.
	* setCellVal - writes a solution to a cell by way of the underlying object's function.
	* getCellVal - returns a solution written in a cell by way of the underlying object's function.
	* setCellNote - sets the 'index' note on a cell to true, uses the underlying object's function.
	* clearCellNote - sets the 'index' note on a cell to false, uses the underlyiing object's function.
	* getCellNote - returns the state of the underlying object's 'index' note.
	* printBoard - outputs the board in a 9x9 format to the console.
	*/
	/* Constructors: */
	SudokuBoard();
	SudokuBoard(int size);
	SudokuBoard(string fileName);
	~SudokuBoard();
	void initBoard(int max);

	/* Board functions: */
	int getBoardSize();
	int getBlockSize();
	void setCellVal(int row, int col, int val);
	int getCellVal(int row, int col);
	void setCellNote(int row, int col, int index, bool set);
	bool getCellNote(int row, int col, int index);
	void printBoard();

	/* Note functions: */
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
	/* Primary data fields: */
	int valMax;
	int blockSize;
	int blockRowStart;
	int blockColStart;
	int blockRowEnd;
	int blockColEnd;
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
		i.resize(valMax);
		for (auto j : i) {
			j = new SudokuCell();
		}
	}*/

	// Set private fields:
	valMax = max;
	blockSize = (int)sqrt(max);

	// Create cell array:
	board.resize(valMax);
	for (int i = 0; i < valMax; i++) {
		board[i].resize(valMax);
		for (int j = 0; j < max; j++) {
			board[i][j] = new SudokuCell(0, valMax);
		}
	}
}

int SudokuBoard::getBoardSize() {
	// Returns the board's maximum value/row size:
	return valMax;
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
	for (int row = 1; row <= valMax; row++) {
		for (int col = 1; col <= valMax; col++) {
			cout << getCellVal(row, col);
			if ((col != valMax) && (col % blockSize == 0)) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		if ((row != valMax) && (row % blockSize == 0)) {
			cout << endl;
			for (int spc = 0; spc < 2*valMax-1; spc++) {
				cout << "-";
			}
		}
		cout << endl;
	}
}