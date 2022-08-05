#include "SudokuCell.h"
#include <stdexcept>


SudokuCell::SudokuCell(int val) {
	setVal(val);
	for (int i = 0; i < 9; i++) {
		notes[i] = false;
	}
}

void SudokuCell::setVal(int val) {
	if (val < 0 || val > 9)
		throw std::out_of_range("Value not accepted");
	cellVal = val;
}

int SudokuCell::getVal() {
	return cellVal;
}

void SudokuCell::setNote(int index) {
	if (index < 0 || index > 9)
		throw std::out_of_range("Index invalid");
		notes[index] = true;
}

bool SudokuCell::getNote(int index) {
	if (index < 0 || index > 9)
		throw std::out_of_range("Note unavailable");
		return notes[index];
}