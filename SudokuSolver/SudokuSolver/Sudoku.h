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
	~Sudoku();

	// Class functions:
	void initGameVals(int size);
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
	SudokuBoard* gameBoard;
};

Sudoku::Sudoku()
{
	gameVals = NULL;
	gameBoard = NULL;
}

Sudoku::Sudoku(int size)
{
	gameBoard = NULL;
	initGameVals(size);
}

Sudoku::Sudoku(SudokuBoard& board)
{
	gameBoard = &board;
	initGameVals(board.getBoardSize());
}

Sudoku::~Sudoku()
{
	delete gameVals;
	delete gameBoard;
}

void Sudoku::initGameVals(int size)
{
	for (int i = 1; i <= size; i++) {
		gameVals->emplace(i, 0);
	}
}

void Sudoku::updateGameVals(int val)
{
	gameVals->at(val) += 1;
}

bool Sudoku::boardSolved()
{
	map<int, int>::iterator val = gameVals->begin();
	int max = gameBoard->getBoardSize();
	while (val != gameVals->end()) {
		if (val->second != max) {
			return false;
		}
		val++;
	}
	return true;
}