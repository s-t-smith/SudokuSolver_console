#pragma once

#include "SudokuBoard.h"
#include <map>

using namespace std;

/*
* This class will define the game state for a session of Sudoku.
* It will contain one SudokuBoard object and pass user IO to the lower objects.
*/

class Sudoku
{
public:
	Sudoku();
	Sudoku(std::string startingFile);
	~Sudoku();
	bool checkRow(int row);
	void clearRowNotes(int row);
	bool checkCol(int col);
	void clearColNotes(int row);
	bool checkBlock(int blk);
	bool checkSolved();
	bool checkGO();
	void printBoard();

private:
	SudokuBoard* gameBoard;
	bool gameOver;
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	gameOver = false;
}

Sudoku::Sudoku(std::string startingFile) {
	gameBoard = new SudokuBoard(startingFile);
	gameOver = false;
}

Sudoku::~Sudoku()
{
	delete gameBoard;
}

bool Sudoku::checkRow(int row) {
	map<int, bool> rowSolutions;
	for (int i = 1; i < 10; i++) {
		rowSolutions[i] = false;
	}

	int checkVal = 0;
	for (int c = 1; c < 10; c++) {
		checkVal = gameBoard->getCellVal(row, c);
		if (checkVal != 0) {
			if (rowSolutions[checkVal]) {
				gameOver = true;
				// Might not want to throw an error and exit, just end the session.
				// throw runtime_error("Out of place solution.");
			}
			rowSolutions[checkVal] = true;
		}
	}

	for (auto const& itr : rowSolutions) {
		if (!itr.second) {
			return false;
		}
	}

	return true;
}

void Sudoku::clearRowNotes(int row) {
	if (checkRow(row)) {
		return;
	}
}

bool Sudoku::checkCol(int col) {
	map<int, bool> colSolutions;
	for (int i = 1; i < 10; i++) {
		colSolutions[i] = false;
	}

	int checkVal = 0;
	for (int r = 1; r < 10; r++) {
		checkVal = gameBoard->getCellVal(r, col);
		if (checkVal != 0) {
			if (colSolutions[checkVal]) {
				gameOver = true;
				// Might not want to throw an error and exit, just end the session.
				// throw runtime_error("Out of place solution.");
			}
			colSolutions[checkVal] = true;
		}
	}

	for (auto const& itr : colSolutions) {
		if (!itr.second) {
			return false;
		}
	}

	return true;
}

void Sudoku::clearColNotes(int col) {
	if (checkRow(col)) {
		return;
	}
}

bool Sudoku::checkBlock(int blk) {
	map<int, bool> blkSolutions;
	for (int i = 1; i < 10; i++) {
		blkSolutions[i] = false;
	}
}

bool Sudoku::checkSolved() {
	return gameBoard->boardSolved();
}

bool Sudoku::checkGO() {
	return gameOver;
}

void Sudoku::printBoard() {
	cout << endl;
	for (int r = 1; r < 10; r++) {
		for (int c = 1; c < 10; c++) {
			cout << "|" << gameBoard->getCellVal(r, c) << "|";
		}
		cout << endl;
	}
	cout << endl;
}