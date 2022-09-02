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
	/*
	* Public functions:
	* Sudoku - Default constructor begins a session with a blank sudoku board.
	* Sudoku(startingFile) - Explicit constructor begins a session with a prepopulated sukoku board.
	* checkRow - looks through an entire row and returns whether or not all values have been entered.
	* checkRowNote - if a note only appears once in a row, return true.
	* clearRowNote - removes all notes for a certain solution in a row.
	* checkCol - looks through an entire column and returns whether or not all values have been entered.
	* checkColNote - if a note only appears once in a column, return true.
	* clearColNote - removes all notes for a certain solution in a column.
	* checkBlock - looks through a 3x3 block and returns whether or not all values have been entered.
	* checkBlockNote - if a note only appears once in a 3x3 block, returns true.
	* clearBlockNote - removes all notes for a certain solution in a 3x3 block.
	* checkSolution - returns the value written to a cell.
	* checkNote - returns the note value for a given cell.
	* writeSolution - sets a cell's solution to a given value.
	* markSolution - records a value as satisfied on the board.
	*	// Might not be useful, going to mark it off for now.
	* checkSolved - returns the state of the board's "isSolved" flag.
	* checkGO - returns the state of the gameOver flag.
	* printBoard - outputs the board to the console window.
	*/
public:
	Sudoku();
	Sudoku(std::string startingFile);
	~Sudoku();
	bool checkRow(int row);
	bool checkRowNote(int row, int val);
	void clearRowNote(int row, int val);
	bool checkCol(int col);
	bool checkColNote(int col, int val);
	void clearColNote(int row, int val);
	bool checkBlock(int blk);
	bool checkBlockNote(int blk, int val);
	void clearBlockNote(int blk, int val);
	int checkSolution(int row, int val);
	bool checkNote(int row, int col, int val);
	void writeSolution(int row, int col, int val);
	// void markSolution(int val);
	bool checkSolved();
	bool checkGO();
	void printBoard();

	/*
	* Private members:
	* gameBoard - 
	* gameOver - check flag that can be used to terminate the session.
	* valuesSolved - keeps track of which solutions have been satisfied on the board.
	*/
private:
	SudokuBoard* gameBoard;
	bool gameOver;
	// bool valuesSolved[9];
		// Might not be useful, going to mark it off for now.
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	
	gameOver = false;
	
	/*
	for (int i = 0; i < 9; i++) {
		valuesSolved[i] = false;
	}
	*/
}

Sudoku::Sudoku(std::string startingFile)
{
	gameBoard = new SudokuBoard(startingFile);
	
	gameOver = false;
	
	/*
	for (int i = 0; i < 9; i++) {
		valuesSolved[i] = false;
	}
	*/
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

void Sudoku::clearRowNote(int row, int val) {
	for (int c = 1; c < 10; c++) {
		gameBoard->clearCellNote(row, c, val);
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

void Sudoku::clearColNote(int col, int val) {
	for (int r = 1; r < 10; r++) {
		gameBoard->clearCellNote(r, col, val);
	}
}

void Sudoku::clearBlockNote(int blk, int val) {

	int row, col;

	switch (blk) {
	case 1:
		row = 1;
		col = 1;
		break;
	case 2:
		row = 1;
		col = 4;
		break;
	case 3:
		row = 1;
		col = 7;
		break;
	case 4:
		row = 4;
		col = 1;
		break;
	case 5:
		row = 4;
		col = 4;
		break;
	case 6:
		row = 4;
		col = 7;
		break;
	case 7:
		row = 7;
		col = 1;
		break;
	case 8:
		row = 7;
		col = 4;
		break;
	case 9:
		row = 7;
		col = 7;
		break;
	default:
		row = 0;
		col = 0;
		break;
	}

	if (row > 0 && col > 0) {
		for (int blkRow = row; blkRow < row + 2; blkRow++) {
			for (int blkCol = col; blkCol < col + 2; blkCol++) {
				gameBoard->clearCellNote(blkRow, blkCol, val);
			}
		}
	}
}

bool Sudoku::checkBlock(int blk) {
	
	map<int, bool> blkSolutions;
	int row, col;
	
	for (int i = 1; i < 10; i++) {
		blkSolutions[i] = false;
	}

	switch (blk) {
	case 1:
		row = 1;
		col = 1;
		break;
	case 2:
		row = 1;
		col = 4;
		break;
	case 3:
		row = 1;
		col = 7;
		break;
	case 4:
		row = 4;
		col = 1;
		break;
	case 5:
		row = 4;
		col = 4;
		break;
	case 6:
		row = 4;
		col = 7;
		break;
	case 7:
		row = 7;
		col = 1;
		break;
	case 8:
		row = 7;
		col = 4;
		break;
	case 9:
		row = 7;
		col = 7;
		break;
	default:
		row = 0;
		col = 0;
		break;
	}

	if (row > 0 && col > 0) {
		int checkVal = 0;
		for (int blkRow = row; blkRow < row + 2; blkRow++) {
			for (int blkCol = col; blkCol < col + 2; blkCol++) {
				checkVal = gameBoard->getCellVal(blkRow, blkCol);
				if (checkVal != 0) {
					if (blkSolutions[checkVal]) {
						gameOver = true;
					}
					blkSolutions[checkVal] = true;
				}
			}
		}
	}

	for (auto const& itr : blkSolutions) {
		if (!itr.second) {
			return false;
		}
	}

	return true;
}

int Sudoku::checkSolution(int row, int col) {
	return gameBoard->getCellVal(row, col);
}

bool Sudoku::checkNote(int row, int col, int val) {
	return gameBoard->getCellNote(row, col, val);
}

void Sudoku::writeSolution(int row, int col, int val) {
	gameBoard->setCellVal(row, col, val);
}

/*
void Sudoku::markSolution(int val) {
	
	if (checkRow(val) && checkCol(val) && checkBlock(val)) {
		valuesSolved[val - 1] = true;
	}
	
	return;
}
*/

bool Sudoku::checkSolved() {
	return gameBoard->boardSolved();
}

bool Sudoku::checkGO() {
	
	if (gameBoard->boardSolved()) {
		gameOver = true;
	}
	
	return gameOver;
}

void Sudoku::printBoard() {
	
	cout << endl;
	
	for (int r = 1; r < 10; r++) {
		for (int c = 1; c < 10; c++) {
			cout << "| ";
			
			if (gameBoard->getCellVal(r, c) == 0) {
				cout << " ";
			}
			
			else {
				cout << gameBoard->getCellVal(r, c);
			}
			
			cout << " |";
		}
		cout << endl;
	}

	cout << endl;
}