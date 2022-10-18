#pragma once

#include "SudokuBoard.h"
#include <fstream>

using namespace std;

/*
* This class will define the game state for a session of Sudoku.
* It will contain one SudokuBoard object and pass user IO to the lower objects.
* 
* This class will also contain some functions that can be called by the main.cpp to implement the solving algorithm.
* 
* This class shall also serve as the index-interpretation layer;
* inputs from SudokuSolver will be 1-indexed and human-readable, while the board layer will be 0-indexed.
*/


class Sudoku
{
	/*
	* Public functions:
	* Sudoku - Default constructor begins a session with a blank sudoku board.
	* Sudoku(startingFile) - Explicit constructor begins a session with a prepopulated sukoku board.
	* 
	* Cell functions:
	* setBoardCellVal - Passes a value down to the board to be written to a cell.
	* getBoardCellVal - Returns the value written to a cell on the board.
	* setBoardCellNote - Marks a note on a board's cell for a possible solution.
	* getBoardCellNote - Returns a note for a solution on a cell from the board.
	* 
	* Board functions:
	* clearRowNotes - Removes all notes for a value along a given row.
	* clearColNotes - Removes all notes for a value along a given column.
	* clearBlockNotes - Removes all notes for a value in a given 3x3 block.
	* isWrittenRow - Checks to see if a solution is present in a given row.
	* isWrittenCol - Checks to see if a solution is present in a given column.
	* isWrittenBlock - Checks to see if a solution is present in a given 3x3 block.
	* 
	* Game functions:
	* printBoard - Output the values written to the board in a 9x9 format to the console.
	* solveBoard - The actual meat-and-potatoes algorithm to put all solutions in their cells.
	*/
public:
	Sudoku();
	Sudoku(std::string startingFile);
	~Sudoku();
	void setBoardCellVal(int val, int row, int col);
	int getBoardCellVal(int row, int col);
	void setBoardCellNote(bool set, int index, int row, int col);
	bool getBoardCellNote(int index, int row, int col);
	void printBoard();
	void clearRowNotes(int val, int row);
	void clearColNotes(int val, int col);
	bool isWrittenRow(int val, int row);
	bool isWrittenCol(int val, int col);
	bool isWrittenBlock(int val, int blk);

	/*
	* Private members:
	* gameBoard - The SudokuBoard object that contains the array of cells.
	* gameOver - Check flag that can be used to terminate the session.
	*/
private:
	SudokuBoard* gameBoard;
	bool gameOver;
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	
	gameOver = false;
	
}

Sudoku::Sudoku(std::string startingFile)
{
	gameBoard = new SudokuBoard();

	int row, col, val = 0;
	ifstream file(startingFile);

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
		setBoardCellVal(val, row-1, col-1);
	}
	
	gameOver = false;
	
}

Sudoku::~Sudoku()
{
	delete gameBoard;
}

void Sudoku::setBoardCellVal(int val, int row, int col) {
	gameBoard->setCellVal(row, col, val);
	clearRowNotes(val, row);
	clearColNotes(val, col);
}

int Sudoku::getBoardCellVal(int row, int col) {
	return gameBoard->getCellVal(row, col);
}

void Sudoku::setBoardCellNote(bool set, int index, int row, int col) {
	if (set) {
		gameBoard->setCellNote(row, col, index);
	}
	else {
		gameBoard->clearCellNote(row, col, index);
	}
}

bool Sudoku::getBoardCellNote(int index, int row, int col) {
	return gameBoard->getCellNote(row, col, index);
}

void Sudoku::printBoard() {
	gameBoard->printBoard();
}

void Sudoku::clearRowNotes(int val, int row) {
	for (int c = 0; c < 9; c++) {
		setBoardCellNote(false, val, row, c);
	}
}

void Sudoku::clearColNotes(int val, int col) {
	for (int r = 0; r < 9; r++) {
		setBoardCellNote(false, val, r, col);
	}
}

bool Sudoku::isWrittenRow(int val, int row) {
	for (int c = 0; c < 9; c++) {
		if (getBoardCellVal(row, c) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::isWrittenCol(int val, int col) {
	for (int r = 1; r < 10; r++) {
		if (getBoardCellVal(r, col) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::isWrittenBlock(int val, int blk) {
	// work in progress
	return false;
}