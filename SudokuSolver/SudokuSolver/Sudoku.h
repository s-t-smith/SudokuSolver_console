#pragma once

#include "SudokuCell.h"
#include "SudokuBoard.h"

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
	* 
	* Board functions:
	* setBoardCellVal - Passes a value down to the board to be written to a cell.
	* getBoardCellVal - Returns the value written to a cell on the board.
	* setBoardCellNote - Marks a note on a board's cell for a possible solution.
	* getBoardCellNote - Returns a note for a solution on a cell from the board.
	* 
	* Game functions:
	* printBoard - Output the values written to the board in a 9x9 format to the console.
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

	/*
	* Private members:
	* gameBoard - The SudokuBoard object that contains the array of cells.
	* gameOver - Check flag that can be used to terminate the session.
	*/
private:
	SudokuBoard* gameBoard;
	bool gameOver;
};

Sudoku::Sudoku()
{
	gameBoard = new SudokuBoard();
	
	gameOver = false;
	
}

Sudoku::Sudoku(std::string startingFile)
{
	gameBoard = new SudokuBoard(startingFile);
	
	gameOver = false;
	
}

Sudoku::~Sudoku()
{
	delete gameBoard;
}

void Sudoku::setBoardCellVal(int val, int row, int col) {
	gameBoard->setCellVal(row, col, val);
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
	gameBoard->getCellNote(row, col, index);
}

void Sudoku::printBoard() {
	for (int r = 1; r < 10; r++) {
		cout << "|";
		for (int c = 1; c < 10; c++) {
			int cellVal = getBoardCellVal(r, c);
			if (cellVal != 0) {
				cout << "| " << cellVal << " |";
			}
			else {
				cout << "|   |";
			}
			
		}
		cout << "|" << endl;
	}
	cout << endl;
}