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
	void updateGameVals(int val);
	bool boardSolved();
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
	// Used for cell dereferencing:
	int blockSize;
	int blockRowStart;
	int blockColStart;
	int blockRowEnd;
	int blockColEnd;
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
	for (int m = 1; m <= maxVal; m++) {
		gameVals->emplace(m, 0);
	}

	// Check the starting board for entries:
	for (int row = 1; row <= maxVal; row++) {
		for (int col = 1; col <= maxVal; col++) {
			int startVal = getBoardCellVal(row, col);
			if(startVal != 0){
				updateGameVals(startVal);
			}
		}
	}
	blockSize = gameBoard->getBlockSize();
	blockRowStart = 0;
	blockRowEnd = 0;
	blockColStart = 0;
	blockColEnd = 0;
}

void Sudoku::updateGameVals(int val)
{
	gameVals->at(val) += 1;
}

bool Sudoku::boardSolved()
{
	map<int, int>::iterator itr = gameVals->begin();
	while (itr != gameVals->end()) {
		if (itr->second != getBoardSize()) {
			return false;
		}
		itr++;
	}
	return true;
}

bool Sudoku::rowValCheck(int row, int val)
{
	for (int col = 1; col <= getBoardSize(); col++) {
		if (getBoardCellVal(row, col) == val) {
			return true;
		}
	}
	return false;
}

void Sudoku::clearRowNotes(int row, int val)
{
	for (int col = 1; col <= getBoardSize(); col++) {
		setBoardCellNote(row, col, val, false);
	}
}

bool Sudoku::colValCheck(int col, int val)
{
	for (int row = 1; row <= getBoardSize(); row++) {
		if (getBoardCellVal(row, col) == val) {
			return true;
		}
	}
	return false;
}

void Sudoku::clearColNotes(int col, int val)
{
	for (int row = 1; row <= getBoardSize(); row++) {
		setBoardCellNote(row, col, val, false);
	}
}

int Sudoku::blockCoord(int row, int col) {
	// Given a set of coordinates, set the cell index limits for looping functions.
	int blockRowRef = (int)((row - 1) / blockSize) * blockSize;	// for 9x9, this recontextualizes the row as 0, 3 or 6.
	int blockColRef = (int)((col - 1) / blockSize) + 1;	// for 9x9, this recontextualizes the col as 1, 2 or 3.
	return blockRowRef + blockColRef;
}

void Sudoku::blockRef(int blk) {
	// Given a single block number, set the cell index limits for looping functions.
	blockRowStart = (((int)(blk - 1) / blockSize) * blockSize) + 1;
	blockRowEnd = blockRowStart + blockSize;
	blockColStart = (((blk - 1) % blockSize) * blockSize) + 1;
	blockColEnd = blockColStart + blockSize;
}

bool Sudoku::blockValCheck(int blk, int val)
{
	blockRef(blk);
	for (int r = blockRowStart; r < blockRowEnd; r++) {
		for (int c = blockColStart; c < blockColEnd; c++) {
			if (getBoardCellVal(r, c) == val)
				return true;
		}
	}
	return false;
}

bool Sudoku::blockValCheck(int row, int col, int val)
{
	return blockValCheck(blockCoord(row, col), val);
}

void Sudoku::clearBlockNotes(int blk, int val)
{
	blockRef(blk);
	for (int r = blockRowStart; r < blockRowEnd; r++) {
		for (int c = blockColStart; c < blockColEnd; c++) {
			setBoardCellNote(r, c, val, false);
		}
	}
}

void Sudoku::clearBlockNotes(int row, int col, int val)
{
	clearBlockNotes(blockCoord(row, col), val);
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
	// Place the solution, then mark the solution in the list:
	gameBoard->setCellVal(row, col, val);

	// Mark the value on the tracker map:
	updateGameVals(val);
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