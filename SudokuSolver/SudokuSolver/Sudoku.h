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

	/*
	* Private members:
	* gameBoard - The SudokuBoard object that contains the 2D array of cells.
	* gameOver - Check flag that can be used to terminate the session.
	*/
private:
	SudokuBoard* gameBoard;
	bool gameOver;
	map<int, int>* boardVals;
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	gameBoard->printBoard();
	gameOver = false;
	boardVals = new map<int, int>;
	for (int i = 0; i < 9; i++) {
		boardVals->emplace(i + 1, 0);
	}
	
}

Sudoku::Sudoku(std::string startingFile)
{
	gameBoard = new SudokuBoard(startingFile);
	gameBoard->printBoard();
	gameOver = false;
	boardVals = new map<int, int>;
	for (int i = 0; i < gameBoard->getBoardSize(); i++) {
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
	gameBoard->printBoard();	// Might pull this up from the board class to implement here, need to consider if that's necessary/worth it.
}

void Sudoku::clearRowNotes(int val, int row) {
	// Set all notes to 'false' along a given row.
	for (auto& i : gameBoard->getBoardSize()) {
		gameBoard->clearCellNote(row, i + 1, val);
	}
}

void Sudoku::clearColNotes(int val, int col) {
	// Set all notes to 'false' along a given column.
	for (auto& i : gameBoard->getBoardSize()) {
		gameBoard->clearCellNote(i + 1, col, val);
	}
}

bool Sudoku::checkRow(int val, int row) {
	// Look for a value along a given row, return 'true' when the value is present.
	for (auto& i : gameBoard->getBoardSize()) {
		if (gameBoard->getCellVal(row, i + 1) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::checkCol(int val, int col) {
	// Look for a value along a given column, return 'true' when the value is present.
	for (auto& i : gameBoard->getBoardSize()) {
		if (gameBoard->getCellVal(i + 1, col) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::checkBlock(int val, int blk) {
	// Look for a value within a given sub-array of the board, return true when the value is present.
	return true;	// Placeholder
	/*
	* This was previously done with a separate class that subdivided the game board, but that layer has been removed in the interest of scalability.
	* Need to come up with a solution for traversing a subarray that can be referential to the orignial array's size.
	*/
}

void Sudoku::checkState() {
	// Count the number of values currently on the board, set the gameOver state based on result:
		// Clear the current counts for a clean read:
	for (auto& val = boardVals->begin(); val != boardVals->end(); val++) {
		boardVals->at(val) = 0;
	}
		// Get new counts:
	for (int r = 0; r < gameBoard->getBoardSize(); r++) {
		for (int c = 0; c < gameBoard->getBoardSize(); c++) {
			int checkVal = gameBoard->getCellVal(r + 1, c + 1);
			boardVals->at(checkVal)++;
		}
	}
		// If all values are present, the game is over:
	for (auto& val = boardVals->begin(); val != boardVals->end(); val++) {
		if (boardVals->at(val) != gameBoard->getBoardSize()) {
			// Any time the count is less than the board max, the game cannot be over:
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