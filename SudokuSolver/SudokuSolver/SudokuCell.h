#pragma once
#include <stdexcept>

/*
* This will be the base-most class for the Sudoku Solver.
* A cell will be where a solution digit is written.
* For this implementation, the cell will also be used for making notes for possible solutions.
*/

class SudokuCell {
/*
* Private members:
* cellVal- Where the cell solution can be written. Can be a digit 0..9.
* notes- Where the possible solutions can be recorded. A 'true' value at an index represents a possible solution of <index>+1.
*/
private:
	int cellVal;
	bool notes[9];
/*
* Public functions:
* SudokuCell() - Default constructor; initializes the cell to "0" with all notes 'false'.
* SudokuCell(int val) - Explicit constructor; initializes the cell with the given digit.
* setVal - Records a digit in the cell's cellVal field.
* getVal - Returns the digit recorded in the cell's cellVal field.
* setNote - Marks a possible solution index as 'true'.
* getNote - Un-marks a possible solution index as 'false'.
* getNote - Returns the solution index requested.
*/
public:
	SudokuCell();
	SudokuCell(int val);
	void setVal(int val);
	int getVal();
	void setNote(int index);
	void clearNote(int index);
	bool getNote(int index);
};

SudokuCell::SudokuCell() {
	// Default constructor sets the cellVal to "0" (unsolved) and loads the notes array.
	setVal(0);
}

SudokuCell::SudokuCell(int val) {
	// Explicit constructor sets the cellVal to the requested digit and clears the notes array.
	setVal(val);
}

void SudokuCell::setVal(int val) {
	// Write a solution digit to the cellVal, prevent out-of-range values.
	if (val < 0 || val > 9)
		throw std::out_of_range("Value not accepted");
	cellVal = val;
	if (cellVal == 0){
		for (int i = 0; i < 9; i++) {
			notes[i] = true;
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			notes[i] = false;
		}
	}
}

int SudokuCell::getVal() {
	return cellVal;
}

void SudokuCell::setNote(int index) {
	// Record a possible solution, prevent out-of-bounds access.
	if (index < 0 || index > 9)
		throw std::out_of_range("Index invalid");
	notes[index] = true;
}

void SudokuCell::clearNote(int index) {
	// Eliminate a possible solution, prevent out-of-bounds access.
	if (index < 0 || index > 9)
		throw std::out_of_range("Index invalid");
	notes[index] = false;
}

bool SudokuCell::getNote(int index) {
	// Report a possible solution, prevent out-of-range access.
	if (index < 0 || index > 9)
		throw std::out_of_range("Note unavailable");
	return notes[index];
}