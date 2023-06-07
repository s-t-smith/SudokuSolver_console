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
	* TODO: finish overhauling this class.
	* 
	* Functions left to make:
	* - something to check the game state; return a bool for game over.
	* - row value checker
	* - column value checker
	* - block value checker
	*/
public:
	Sudoku();
	Sudoku(int size);
	Sudoku(std::string startingFile);
	~Sudoku();

	// Class functions:
	void initGameVals();

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
	
	// Create an entry for 
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