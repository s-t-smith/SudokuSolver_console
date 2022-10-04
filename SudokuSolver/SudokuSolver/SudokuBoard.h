#pragma once

#include "SudokuCell.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

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
	* SudokuBoard(string inputPath) - Explicit constructor; makes a board object pre-populated with some cell values.
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
	SudokuBoard(std::string inputPath);
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
	SudokuCell* board[9][9];
		// If I change to vectors, this could scale better, and I could use iterators, which might be handy for blocks.
};


SudokuBoard::SudokuBoard() {
	// Creates a 9x9 set of empty SudokuCell objects.
	for (int r = 0; r < 9; r++) {
		
		// Create empty cells:
		for (int c = 0; c < 9; c++) {
			board[r][c] = new SudokuCell();
		}
	}
}

SudokuBoard::SudokuBoard(std::string inputPath) {
	// Creates a blank 9x9 board like the default constructor...
	for (int r = 0; r < 9; r++) {

		for (int c = 0; c < 9; c++) {
			board[r][c] = new SudokuCell();
		}
	}
	// ...then populates cells based on the input file.
	int row, col, val = 0;
	ifstream file(inputPath);

	if (!file.is_open()) {
		throw runtime_error("Could not open file.");
	}

	// Input files should be .txt where each line is as follows:
	// <row #> <col #> <number (1..9)>
	// The following loop will extract each value and use them to call the setVal() of the relevant cell.
	while (!file.eof()) {
		file >> row;
		file >> col;
		file >> val;
		setCellVal(row, col, val);
	}
}

SudokuBoard::~SudokuBoard() {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			delete board[r][c];
		}
	}
}

void SudokuBoard::setCellVal(int row, int col, int val) {
	// Coordinates are assumed as input in user format (1..9) while array references are machine indexed (0..8)
	board[row - 1][col - 1]->setVal(val);
}

int SudokuBoard::getCellVal(int row, int col) {
	// Coordinates are assumed as input in user format (1..9) while array references are machine indexed (0..8)
	return board[row - 1][col - 1]->getVal();
}

void SudokuBoard::setCellNote(int row, int col, int index) {
	// Coordinates are assumed as input in user format (1..9) while array references are machine indexed (0..8)
	board[row - 1][col - 1]->setNote(index - 1);
}

void SudokuBoard::clearCellNote(int row, int col, int index) {
	// Coordinates are assumed as input in user format (1..9) while array references are machine indexed (0..8)
	board[row - 1][col - 1]->clearNote(index - 1);
}

bool SudokuBoard::getCellNote(int row, int col, int index) {
	// Coordinates are assumed as input in user format (1..9) while array references are machine indexed (0..8)
	return board[row - 1][col - 1]->getNote(index - 1);
}

void SudokuBoard::printBoard() {
	int cellVal = 0;
	cout << endl;
	cout << "Current board:" << endl;
	for (int c = 0; c < 9; c++) {
		cout << "|";
		for (int r = 0; r < 9; r++) {
			cellVal = board[r][c]->getVal();
			if (cellVal == 0) {
				cout << "| |";
			}
			else {
				cout << "|" << cellVal << "|";
			}
		}
		cout << endl;
	}
	cout << endl;
}