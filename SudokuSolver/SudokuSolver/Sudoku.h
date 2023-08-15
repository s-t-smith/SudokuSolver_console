#pragma once

#include "SudokuBoard.h"
#include <map>
#include <string>

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
	Sudoku(SudokuBoard& board);
	Sudoku(string filename);
	~Sudoku();

	// Class functions:
	void initGameVals(int size);
	void updateGameVals();
	void updateGameVals(int val);
	bool boardSolved();
	
	/* These should be accessible directly */
	// Board-layer functions:
	/*int getBoardSize();
	int getBoardCellVal(int row, int col);
	void setBoardCellVal(int row, int col, int val);
	bool getBoardCellNote(int row, int col, int idx);
	void setBoardCellNote(int row, int col, int idx, bool set);*/
	void printGameBoard();

private:
	/* Game state monitors:*/
	map<const int, int> gameVals;
	SudokuBoard* gameBoard;
};

Sudoku::Sudoku()
{
	gameBoard = NULL;
}

Sudoku::Sudoku(int size)
{
	gameBoard = new SudokuBoard(size);
	initGameVals(size);
}

Sudoku::Sudoku(SudokuBoard& board)
{
	gameBoard = &board;
	initGameVals(gameBoard->getBoardSize());
	updateGameVals();
}

Sudoku::Sudoku(string filename)
{
	gameBoard = new SudokuBoard(filename);
	initGameVals(gameBoard->getBoardSize());
	updateGameVals();
}

Sudoku::~Sudoku()
{
	// this causes issues in unit test; investigate:
	// delete gameBoard;
}

void Sudoku::initGameVals(int size)
{
	for (int i = 0; i < size; i++) {
		gameVals.emplace(i+1, 0);
	}
}

void Sudoku::updateGameVals()
{
	for (int r = 1; r <= gameBoard->getBoardSize(); r++) {
		for (int c = 1; c <= gameBoard->getBoardSize(); c++) {
			updateGameVals(gameBoard->getCellVal(r, c));
		}
	}
}

void Sudoku::updateGameVals(int val)
{
	try { gameVals.at(val) += 1; }
	catch (...) { return; }
}

bool Sudoku::boardSolved()
{
	map<int, int>::iterator val = gameVals.begin();
	int max = gameBoard->getBoardSize();
	while (val != gameVals.end()) {
		if (val->second != max) {
			return false;
		}
		val++;
	}
	return true;
}

void Sudoku::printGameBoard()
{
	gameBoard->printBoard();
}