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
	void initBoard(int max, int block);
	int getBoardSize();
	SudokuCell& targetCell(int row, int col);
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
	initBoard(9, 3);
}

SudokuBoard::SudokuBoard(int size) {
	// Create a square array of <size>:
	double checkSR = sqrt(size);
	if (ceil(checkSR) == floor(checkSR)) {
		initBoard(size, (int) checkSR);
	}
	else {
		// If the given size isn't a perfect square, default to a 9x9 board:
		initBoard(9, 3);
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
		double checkSR = sqrt(inputSize);
		if (ceil(checkSR) == floor(checkSR)) {
			initBoard(inputSize, (int)checkSR);
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
		initBoard(9, 3);
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
void SudokuBoard::initBoard(int max, int block) {
	// Set a default board size of 9x9:
	valMax = max;
	board.resize(block);
	// No workie:
	/*for (auto i : board) {
		i.resize(valMax);
		for (auto j : i) {
			j = new SudokuCell();
		}
	}*/
	for (int i = 0; i < block; i++) {
		board[i].resize(block);
		for (int j = 0; j < block; j++) {
			board[i][j] = new SudokuBlock(block);
		}
	}
}

int SudokuBoard::getBoardSize() {
	// Returns the board's maximum value/row size:
	return valMax;
}

// Helps dereference a cell from the 1-ref row and col values:
SudokuCell& SudokuBoard::targetCell(int row, int col) {
	// TODO: figure this out.
}

void SudokuBoard::setCellVal(int row, int col, int val) {
	SudokuCell* target = targetCell(row, col);
	target->setVal(val);
}

int SudokuBoard::getCellVal(int row, int col) {
	SudokuCell* target = targetCell(row, col);
	return target->getVal();
}

void SudokuBoard::setCellNote(int row, int col, int index, bool set) {
	SudokuCell* target = targetCell(row, col);
	target->setNote(index, set);
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	SudokuCell* target = targetCell(row, col);
	return target->getNote(index);
}

void SudokuBoard::printBoard() {
	// TODO: rewrite this to incorporate blocks.
}