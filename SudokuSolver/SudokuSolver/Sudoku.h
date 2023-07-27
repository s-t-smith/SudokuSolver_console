#pragma once

#include "SudokuBoard.h"
#include <map>

using namespace std;

/*
* This class will define the game state for a session of Sudoku.
*/


class Sudoku
{
	/*
	* TODO: re-document the classes...
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
	
	/* These should be accessible directly */
	// Board-layer functions:
	/*int getBoardSize();
	int getBoardCellVal(int row, int col);
	void setBoardCellVal(int row, int col, int val);
	bool getBoardCellNote(int row, int col, int idx);
	void setBoardCellNote(int row, int col, int idx, bool set);
	void printGameBoard();*/

private:
	/* Game state monitors:*/
	map<int, int>* gameVals;
	// SudokuBoard* gameBoard;

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