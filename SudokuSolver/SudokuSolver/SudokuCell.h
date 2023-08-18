#pragma once
#include <stdexcept>
#include <vector>

/*
* This will be the base-most class for the Sudoku Solver.
* A cell will be where a solution digit is written.
* For this implementation, the cell will also be used for making notes for possible solutions.
*/

class SudokuCell {

private:
/*
* Private members:
* cellVal- Where the cell solution can be written. Can be a digit 0..<max>.
* notes- Where the possible solutions can be recorded. A 'true' value at an index represents a possible solution of <index>+1.
*/
	int cellVal;
	std::vector<bool> notes;

public:
	/* CONSTRUCTORS:
	* SudokuCEll(int val, int size)-
	*	creates a cell object with the given value written and a list of notes of the given size.
	*/
	SudokuCell();
	SudokuCell(int val, int size);
	/* CELL FUNCTIONS:
	* setVal(int val)-
	*	writes the value to the cell.
	* getVal()-
	*	returns the value writte to the cell.
	* getSize()-
	*	returns the length of the notes list.
	* setNote(int index, bool set)-
	*	sets the notes list item at the given index to true or false.
	* getNote(int index)-
	*	returns the note list at the given index.
	*/
	void setVal(int val);
	int getVal();
	int getSize();
	void setNote(int index, bool set);
	bool getNote(int index);
};

SudokuCell::SudokuCell() {
	notes.resize(9);
	setVal(0);
}

SudokuCell::SudokuCell(int val, int size) {
	notes.resize(size);
	setVal(val);
}

void SudokuCell::setVal(int val) {
	// Write a solution digit to the cellVal, prevent out-of-range values:
	if (val < 0 || val > (int) notes.size())
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
	return (int) notes.size();
}

void SudokuCell::setNote(int index, bool set) {
	// Record a possible solution, prevent out-of-bounds access.
	if (index < 0 || index > (int) notes.size())
		throw std::out_of_range("Index invalid");
	notes[index] = set;
}

bool SudokuCell::getNote(int index) {
	// Report a possible solution, prevent out-of-range access.
	if (index < 0 || index > (int) notes.size())
		throw std::out_of_range("Note unavailable");
	return notes[index];
}