#include "SudokuCell.h"
#include <stdexcept>

SudokuCell::SudokuCell(){
	// Default constructor sets the cellVal to "0" (unsolved) and clears the notes array.
	setVal(0);
	for (int i = 0; i < 9; i++) {
		notes[i] = false;
	}
}

SudokuCell::SudokuCell(int val) {
	// Explicit constructor sets the cellVal to the requested digit and clears the notes array.
	setVal(val);
	for (int i = 0; i < 9; i++) {
		notes[i] = false;
	}
}

void SudokuCell::setVal(int val) {
	// Write a solution digit to the cellVal, prevent out-of-range values.
	if (val < 0 || val > 9)
		throw std::out_of_range("Value not accepted");
	cellVal = val;
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