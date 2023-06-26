#pragma once

#include "SudokuBoard.h"
#include <fstream>
#include <map>

using namespace std;

/*
* This class will define the game state for a session of Sudoku.
* It will contain one SudokuBoard object and pass user IO to the lower objects.
*/


class Sudoku
{
	/*
	* Class functions:
	* - initGameVals: Records the board's max value and records the initial values written to the board.
	* - boardSolved: Checks the log of written values. Returns true if each value has only the maximum number of entries.
	* - rowValCheck: Checks all cell columns in a given row for a value. Returns true if the value is written to any cell. 
	* - colValCheck: Checks all cell rows in a given column for a value. Returns true if the value is written to any cell.
	* - blockValCheck: Uses a block index to check a subarray of cells for a value (1..9 for a 9x9 board). Returns true if the value is written to any cell.
	* 
	* Board-layer functions simply pass the arguements down to the underlying SudokuBoard object.
	*/
public:
	Sudoku();
	Sudoku(int size);
	Sudoku(std::string startingFile);
	~Sudoku();

	// Class functions:
	void initGameVals();
	bool boardSolved();
	bool rowValCheck(int row, int val);
	bool colValCheck(int col, int val);
	bool blockValCheck(int blk, int val);

	// Board-layer functions:
	int getBoardSize();
	int getBoardCellVal(int row, int col);
	void setBoardCellVal(int row, int col, int val);
	bool getBoardCellNote(int row, int col, int idx);
	void setBoardCellNote(int row, int col, int idx, bool set);
	void printGameBoard();

private:
	SudokuBoard* gameBoard;
	map<int, int>* gameVals;
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	gameVals = new map<int, int>;
	initGameVals();
}

Sudoku::Sudoku(int size)
{
	gameBoard = new SudokuBoard(size);
	gameVals = new map<int, int>;
	initGameVals();
}

Sudoku::Sudoku(std::string startingFile)
{
	gameBoard = new SudokuBoard(startingFile);
	gameVals = new map<int, int>;
	initGameVals();
}

Sudoku::~Sudoku()
{
	delete gameBoard;
	delete gameVals;
}

void Sudoku::initGameVals()
{
	int maxVal = getBoardSize();
	
	// Create an entry for each solution
	for (int m = 0; m < maxVal; m++) {
		gameVals->emplace(m + 1);
	}

	// Check the starting board for entries:
	for (int row = 0; row < maxVal; row++) {
		for (int col = 0; col < maxVal; col++) {
			gameVals->at(getBoardCellVal(row, col))++;
		}
	}
}

bool Sudoku::boardSolved()
{
	auto itr = gameVals->begin();
	while (itr != gameVals->end()) {
		if (itr->second != getBoardSize()) {
			return false;
		}
	}
	return true;
}

bool Sudoku::rowValCheck(int row, int val)
{
	for (int col = 0; col < getBoardSize(); col++) {
		if (getBoardCellVal(row, col) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::colValCheck(int col, int val)
{
	for (int row = 0; row < getBoardSize(); row++) {
		if (getBoardCellVal(row, col) == val) {
			return true;
		}
	}
	return false;
}

bool Sudoku::blockValCheck(int blk, int val)
{
	// Auto-false when receiving a bad block index:
	if ((blk < 0) || (blk > getBoardSize())) {
		return false;
	}

	int rowOffset = 0;
	int colOffset = 0;
	int blockLimit = (int)sqrt(getBoardSize());

	// Dereference row and column values from a block index:
	rowOffset = (int)((blk - 1) / blockLimit) * blockLimit + 1;
	colOffset = ((blk - 1) % blockLimit) * blockLimit + 1;

	// Check a block for a value:
	for (int row = rowOffset; row < rowOffset + blockLimit; row++) {
		for (int col = colOffset; col < colOffset + blockLimit; col++) {
			if (getBoardCellVal(row, col) != val) {
				return false;
			}
		}
	}
	return true;
}

int Sudoku::getBoardSize()
{
	return gameBoard->getBoardSize();
}

int Sudoku::getBoardCellVal(int row, int col)
{
	return gameBoard->getCellVal(row, col);
}

void Sudoku::setBoardCellVal(int row, int col, int val)
{
	gameBoard->setCellVal(row, col, val);
	gameVals->at(val)++;
}

bool Sudoku::getBoardCellNote(int row, int col, int idx)
{
	return gameBoard->getCellNote(row, col, idx);
}

void Sudoku::setBoardCellNote(int row, int col, int idx, bool set)
{
	gameBoard->setCellNote(row, col, idx, set);
}

void Sudoku::printGameBoard()
{
	gameBoard->printBoard();
}