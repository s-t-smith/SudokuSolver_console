#pragma once
#include <stdexcept>
#include <vector>

/*
* This will be the base-most class for the Sudoku Solver.
* A cell will be where a solution digit is written.
* For this implementation, the cell will also be used for making notes for possible solutions.
*/

class SudokuCell {
/*
* Private members:
* cellVal- Where the cell solution can be written. Can be a digit 0..<max>.
* notes- Where the possible solutions can be recorded. A 'true' value at an index represents a possible solution of <index>+1.
*/
private:
	int cellVal;
	std::vector<bool> notes;
/*
* Public functions:
* SudokuCell() - Default constructor; initializes the cell to "0" with all notes 'true'.
* SudokuCell(int val, int size) - Explicit constructor; initializes the cell with the given digit and sets the number of notes.
* setVal - Records a digit in the cell's cellVal field.
* getVal - Returns the digit recorded in the cell's cellVal field.
* setNote - Marks a possible solution index as 'true'.
* getNote - Un-marks a possible solution index as 'false'.
* getNote - Returns the solution index requested.
*/
public:
	// Default constructor assumes 9x9 board:
	SudokuCell();
	// Explicit constructor allocates for maximum board size (default to 9x9):
	SudokuCell(int val, int size);
	void setVal(int val);
	int getVal();
	int getSize();
	void setNote(int index);
	void clearNote(int index);
	bool getNote(int index);
};

SudokuCell::SudokuCell() {
	notes.resize(9);
	setVal(0);
}

SudokuCell::SudokuCell(int val, int size = 9) {
	notes.resize(size);
	setVal(val);
}

void SudokuCell::setVal(int val) {
	// Write a solution digit to the cellVal, prevent out-of-range values:
	if (val < 0 || val > notes.size())
		throw std::out_of_range("Value not accepted");
	// Set valid value to private member:
	cellVal = val;
	// Clear or set notes as appropriate for the value set:
	if (cellVal == 0){
		for (auto i : notes) {
			i = true;
		}
	}
	else {
		for (auto i : notes) {
			i = false;
		}
	}
}

int SudokuCell::getVal() {
	return cellVal;
}

int SudokuCell::getSize() {
	return notes.size();
}

void SudokuCell::setNote(int index) {
	// Record a possible solution, prevent out-of-bounds access.
	if (index < 0 || index > notes.size())
		throw std::out_of_range("Index invalid");
	notes[index] = true;
}

void SudokuCell::clearNote(int index) {
	// Eliminate a possible solution, prevent out-of-bounds access.
	if (index < 0 || index > notes.size())
		throw std::out_of_range("Index invalid");
	notes[index] = false;
}

bool SudokuCell::getNote(int index) {
	// Report a possible solution, prevent out-of-range access.
	if (index < 0 || index > notes.size())
		throw std::out_of_range("Note unavailable");
	return notes[index];
}