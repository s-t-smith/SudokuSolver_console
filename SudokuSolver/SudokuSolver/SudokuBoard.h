#pragma once

//#include "SudokuBlock.h"
//	This scalable implementation won't use the block class.
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
public:
	SudokuBoard();
	SudokuBoard(int size);
	SudokuBoard(string fileName);
	~SudokuBoard();
	int getBoardSize();
	void setCellVal(int row, int col, int val);
	int getCellVal(int row, int col);
	void setCellNote(int row, int col, int index);
	void clearCellNote(int row, int col, int index);
	bool getCellNote(int row, int col, int index);
	void printBoard();

	/*
	* Private members:
	* board - an array of SudokuCell objects.
	* valMax - the maximum value of cell solutions; also the number of rows and columns.
	*/
private:
	int valMax;
	vector<vector<SudokuCell*>> board;
};


SudokuBoard::SudokuBoard() {
	// Set a default board size of 9x9:
	valMax = 9;
	board.resize(valMax);
	// No workie:
	/*for (auto i : board) {
		i.resize(valMax);
		for (auto j : i) {
			j = new SudokuCell();
		}
	}*/
	for (int i = 0; i < valMax; i++) {
		board[i].resize(valMax);
		for (int j = 0; j < valMax; j++) {
			board[i][j] = new SudokuCell();
		}
	}
}

SudokuBoard::SudokuBoard(int size) {
	// Create a square array of <size>:
	valMax = size;
	board.resize(size);
	/*for (auto i : board) {
		i.resize(size);
		for (auto j : i) {
			j = new SudokuCell(0, size);
		}
	}*/
	for (int i = 0; i < size; i++) {
		board[i].resize(valMax);
		for (int j = 0; j < size; j++) {
			board[i][j] = new SudokuCell(0, valMax);
		}
	}
}

SudokuBoard::SudokuBoard(string fileName) : SudokuBoard(9){
	int inputSize, inputRow, inputCol, inputVal;
	ifstream inputFile;
	inputFile.open(fileName);
	if (inputFile.is_open()) {
		// First character should be the board size/max value:
		inputFile >> inputSize;
		// Create empty board:
		valMax = inputSize;
		board.resize(inputSize);
		/*for (auto i : board) {
			i.resize(inputSize);
			for (auto j : i) {
				j = new SudokuCell(0, inputSize);
			}
		}*/
		for (int i = 0; i < valMax; i++) {
			board[i].resize(valMax);
			for (int j = 0; j < valMax; j++) {
				board[i][j] = new SudokuCell(0, valMax);
			}
		}
		// Populate cell values:
		while (!inputFile.eof()) {
			inputFile >> inputRow;
			inputFile >> inputCol;
			inputFile >> inputVal;
			setCellVal(inputRow, inputCol, inputVal);
		}
		inputFile.close();
	}
	else {
		// throw invalid_argument("Failed to read file.");
		// SudokuBoard();
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

int SudokuBoard::getBoardSize() {
	// Returns the board's maximum value/row size:
	return valMax;
}

void SudokuBoard::setCellVal(int row, int col, int val) {
	// Write a value to a cell; invalid values will be discarded:
	if (val < 0 || val > valMax) {
		throw out_of_range("Value not accepted");
	}
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	// Row and column must be 0-ref, arguments may be read from a file as 1-ref:
	board[adjustedRow][adjustedCol]->setVal(val);
}

int SudokuBoard::getCellVal(int row, int col) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	// Read the value from a cell:
	return board[adjustedRow][adjustedCol]->getVal();
}

void SudokuBoard::setCellNote(int row, int col, int index) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	int adjustedIndex = index - 1;
	// Write a possible solution to a cell:
	board[adjustedRow][adjustedCol]->setNote(adjustedIndex);
}

void SudokuBoard::clearCellNote(int row, int col, int index) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	int adjustedIndex = index - 1;
	// Discard a possible solution from a cell:
	board[adjustedRow][adjustedCol]->clearNote(adjustedIndex);
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	int adjustedIndex = index - 1;
	// Read a possible solution on a cell:
	return board[adjustedRow][adjustedCol]->getNote(adjustedIndex);
}

void SudokuBoard::printBoard() {
	int counter = 0;
	// Display the cell values at time of call:
	cout << endl;
	cout << "Current board:" << endl;
	cout << endl;
	for (auto r : board) {
		cout << "|";
		for (auto c : r) {
			++counter;
			if(c->getVal() != 0){ 
				cout << c->getVal();
			}
			else {
				cout << "-";
			}
			if (counter % (int)sqrt(valMax) == 0) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
		if (counter % ((int)sqrt(valMax)*valMax) == 0) {
			cout << endl;
		}
	}
	cout << endl;
}