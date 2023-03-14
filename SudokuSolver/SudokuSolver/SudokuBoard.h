#pragma once

//#include "SudokuBoard.h"
//	This scalable implementation won't use the board class.
#include "SudokuCell.h"
#include <string>
#include <iostream>

using namespace std;

/*
* This class will define the game space for a session of Sudoku.
*/

class SudokuBoard
{
	/*
	* Public functions:
	* SudokuBoard() - Default constructor; makes an empty board object with no values written to any cells.
	* SudokuBoard(int size) - Explicit constructor; makes an empty board with a user-provider number of rows and columns.
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
	// SudokuBoard();
	SudokuBoard(int size = 9);
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


/*SudokuBoard::SudokuBoard() {
	// Set a default board size of 9x9:
	valMax = 9;
	board.resize(9);
	for (auto i : board) {
		i.resize(9);
		for (auto j : i) {
			j = new SudokuCell();
		}
	}
}*/

SudokuBoard::SudokuBoard(int size) {
	// Set a user-given size:
	valMax = size;
	board.resize(size);
	for (auto i : board) {
		i.resize(size);
		for (auto j : i) {
			j = new SudokuCell();
		}
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
	board[row][col]->setVal(val);
}

int SudokuBoard::getCellVal(int row, int col) {
	// Read the value from a cell:
	return board[row][col]->getVal();
}

void SudokuBoard::setCellNote(int row, int col, int index) {
	// Write a possible solution to a cell:
	board[row][col]->setNote(index);
}

void SudokuBoard::clearCellNote(int row, int col, int index) {
	// Discard a possible solution from a cell:
	board[row][col]->clearNote(index);
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	// Read a possible solution on a cell:
	return board[row][col]->getNote(index);
}

void SudokuBoard::printBoard() {
	// Display the cell values at time of call:
	cout << endl;
	cout << "Current board:" << endl;
	for (auto r : board) {
		cout << "|";
		for (auto c : r) {
			cout << c->getVal() << "|";
		}
		cout << endl;
	}
	cout << endl;
}