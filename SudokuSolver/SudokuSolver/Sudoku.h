#pragma once

#include "SudokuBoard.h"
#include <fstream>
#include <map>

using namespace std;

/*
* This class will define the game state for a session of Sudoku.
* It will contain one SudokuBoard object and pass user IO to the lower objects.
* 
* This class will also contain some functions that will implement the solving algorithm.
*/


class Sudoku
{
	/*
	* Public functions:
	* Sudoku - Default constructor begins a session with a blank sudoku board.
	* Sudoku(startingFile) - Explicit constructor begins a session with a prepopulated sukoku board.
	* 
	* Cell functions (from the board class):
	* setBoardCellVal - Passes a value down to the board to be written to a cell.
	* getBoardCellVal - Returns the value written to a cell on the board.
	* setBoardCellNote - Marks a note on a board's cell for a possible solution.
	* getBoardCellNote - Returns a note for a solution on a cell from the board.
	* 
	* Board functions (for solving the board):
	* clearRowNotes - Removes all notes for a value along a given row.
	* clearColNotes - Removes all notes for a value along a given column.
	* clearBlockNotes - Removes all notes for a value in a given 3x3 block.
	* checkRow - Checks to see if a solution is present in a given row.
	* checkCol - Checks to see if a solution is present in a given column.
	* checkBlock - Checks to see if a solution is present in a given 3x3 block.
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
	bool checkRow(int val, int row);
	bool checkCol(int val, int col);
	bool checkBlock(int val, int blk);
	void checkState();
	bool checkGO();
	int getBoardSize();

	/*
	* Private members:
	* gameBoard - The SudokuBoard object that contains the 2D array of cells.
	* bockable - Used to enable the checkBlock() method.
	* gameOver - Check flag that can be used to terminate the session.
	* solved - Used in tandem with the gameOver flag; a game can be over but not solved.
	* boardVals - Used to track the solutions on the board.
	*/
private:
	SudokuBoard* gameBoard;
	bool blockable;
	bool gameOver;
	bool solved;	// To do: implement this in the checkState() method.
	map<int, int>* boardVals;
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	gameBoard->printBoard();
	if (getBoardSize() % (int) sqrt(getBoardSize()) == 0) {
		blockable = true;
	}
	else {
		blockable = false;
	}
	gameOver = false;
	boardVals = new map<int, int>;
	for (int i = 0; i < 9; i++) {
		boardVals->emplace(i + 1, 0);
	}
}

Sudoku::Sudoku(std::string startingFile)
{
	gameBoard = new SudokuBoard(startingFile);
	if (getBoardSize() % (int)sqrt(getBoardSize()) == 0) {
		blockable = true;
	}
	else {
		blockable = false;
	}
	gameOver = false;
	boardVals = new map<int, int>;
	for (int i = 0; i < getBoardSize(); i++) {
		boardVals->emplace(i + 1, 0);
	}
	checkState();
}

Sudoku::~Sudoku()
{
	delete gameBoard;
	delete boardVals;
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
	gameBoard->setCellNote(row, col, index, set);
}

bool Sudoku::getBoardCellNote(int index, int row, int col) {
	return gameBoard->getCellNote(row, col, index);
}

void Sudoku::printBoard() {
	gameBoard->printBoard();
}

void Sudoku::clearRowNotes(int val, int row) {
	// Set all notes to 'false' along a given row.
	for (int i = 1; i <= getBoardSize(); i++) {
		setBoardCellNote(0, val, row, i);
	}
}

void Sudoku::clearColNotes(int val, int col) {
	// Set all notes to 'false' along a given column.
	for (int i = 1; i <= getBoardSize(); i++) {
		setBoardCellNote(0, val, i, col);
	}
}

bool Sudoku::checkRow(int val, int row) {
	// Look for a value along a given row, return 'true' when the value is present.
	for (int i = 1; i <= getBoardSize(); i++) {
		if (getBoardCellVal(row, i) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::checkCol(int val, int col) {
	// Look for a value along a given column, return 'true' when the value is present.
	for (int i = 1; i <= getBoardSize(); i++) {
		if (getBoardCellVal(i, col) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::checkBlock(int val, int blk) {
	if (blk <= 0 || blk > pow(getBoardSize(), 2)) {
		return false;
	}
	// Set the offset values based on block requested:
	int rowOffset = 0;
	int colOffset = 0;
		// To do: figure this out.
	// Look for a value within a given sub-array of the board, return true when the value is present.
	for (int r = 1; r <= (int)sqrt(getBoardSize()); r++) {
		for (int c = 1; c <= (int) sqrt(getBoardSize()); c++) {
			if (getBoardCellVal(r + rowOffset, c + colOffset) == val) {
				return true;
			}
		}
	}
	return false;
	/*
	* This was previously done with a separate class that subdivided the game board, but that layer has been removed in the interest of scalability.
	* Need to come up with a solution for traversing a subarray that can be referential to the orignial array's size.
	*/
}

void Sudoku::checkState() {
	
	map<int, int>::iterator val;
	// Count the number of values currently on the board, set the gameOver state based on result:
		// Clear the current counts for a clean read:
	for (val = boardVals->begin(); val != boardVals->end(); val++) {
		val->second = 0;
	}
		// Get new counts:
	for (int r = 1; r <= getBoardSize(); r++) {
		for (int c = 1; c <= getBoardSize(); c++) {
			int checkVal = getBoardCellVal(r, c);
			if(checkVal!=0){ 
				boardVals->at(checkVal)++; }
		}
	}
		// If all values are present, the game is over:
	for (val = boardVals->begin(); val != boardVals->end(); val++) {
		if (val->second != getBoardSize()) {
			// Any time the count is less than the board max (or greater than, for whatever reason), the game cannot be over:
			gameOver = false;
			return;
		}
	}
	gameOver = true;
	return;
}

bool Sudoku::checkGO() {
	return gameOver;
}

int Sudoku::getBoardSize() {
	return gameBoard->getBoardSize();
}