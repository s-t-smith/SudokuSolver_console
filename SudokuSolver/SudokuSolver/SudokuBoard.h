#pragma once

//#include "SudokuBlock.h"
//	This scalable implementation won't use the block class.
#include "SudokuBlock.h"
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
	void setCellNote(int row, int col, int index, bool set);
	bool getCellNote(int row, int col, int index);
	void printBoard();

	/*
	* Private members:
	* board - an array of SudokuCell objects.
	* valMax - the maximum value of cell solutions; also the number of rows and columns.
	*/
private:
	int valMax;
	vector<vector<SudokuBlock*>> board;
};


SudokuBoard::SudokuBoard() {
	// Set a default board size of 9x9:
	valMax = 9;
	board.resize(3);
	// No workie:
	/*for (auto i : board) {
		i.resize(valMax);
		for (auto j : i) {
			j = new SudokuCell();
		}
	}*/
	for (int i = 0; i < 3; i++) {
		board[i].resize(3);
		for (int j = 0; j < 3; j++) {
			board[i][j] = new SudokuBlock();
		}
	}
}

SudokuBoard::SudokuBoard(int size) {
	// Create a square array of <size>:
	
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
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	// TODO: rewrite this to incorporate blocks.
}

int SudokuBoard::getCellVal(int row, int col) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	// TODO: rewrite this to incorporate blocks.
}

void SudokuBoard::setCellNote(int row, int col, int index, bool set) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	int adjustedIndex = index - 1;
	// TODO: rewrite this to incorporate blocks.
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	// Inputs are 1-ref, arrays are 0-ref; adjust the input for the lower layers:
	int adjustedRow = row - 1;
	int adjustedCol = col - 1;
	int adjustedIndex = index - 1;
	// TODO: rewrite this to incorporate blocks.
}

void SudokuBoard::printBoard() {
	// TODO: rewrite this to incorporate blocks.
}