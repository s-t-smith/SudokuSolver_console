#pragma once

#include "SudokuBoard.h"
#include <map>
#include <string>

using namespace std;

/*
* This class will define and monitor the game state for a session of Sudoku.
*/


class Sudoku
{
	
public:
	/* CONSTRUCTORS:
	* Sudoku(int size)-
	*	starts the game state monitor with a given board size and maximum solution value.
	* Sudoku(SudokuBoard& board)-
	*	used when a board object already exists; sets the monitor for a given game board.
	* Sudoku(string filename)-
	*	used when a board objest does NOT already exist; creates a board object from a starting file and sets the monitor.
	*/
	Sudoku();
	Sudoku(int size);
	Sudoku(SudokuBoard& board);
	Sudoku(string filename);
	~Sudoku();

	/* CLASS FUNCTIONS:
	* initGameVals(int size)-
	*	initializes the monitor values with a given maximum solution value.
	* updateGameVals()-
	*	only to be used with constructors; makes an initial pass over the starting board to record the prepopulated values.
	* updateGameVals(int val)-
	*	used to increment a solution value in the monitor when it is written to the game board.
	* boardSolved()-
	*	checks the solution values to determine if the game has been completed.
	*/
	void initGameVals(int size);
	void updateGameVals();
	void updateGameVals(int val);
	bool boardSolved();
	
	/* MAP ACCESSORS:
	These expose a little of the value tracking map to other classes.
	* lowest()-
	*	points to the lowest solution values, usually the "1" position.
	* highest()-
	*	points to the game's maximum solution values, "9" postion for standard games.
	*/
	map<const int, int>::const_iterator lowest() { return gameVals.begin(); }
	map<const int, int>::const_iterator highest() { return gameVals.end(); }

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
	// this causes issues in unit test; investigate...
	// presumably becuase the user should be able to destroy the Sudoku object without destroying the board object.
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