#pragma once

#include "SudokuCell.h"

/*
* This is an intermediate class intended to help the higher layers organize and dereference a full board array.
* A "block" will consist of 9 SudokuCell objects in a 3x3 array.
*/

class SudokuBlock
{
/* 
* This class will be a simple collection of lower-level objects.
* The functions of those objects will be explosed through this layer's public functions:
* SudokuBlock - Default constructor. No explicit constructor is implemented for this project, which would require some tricky argument passing from the higher layers.
* ~SudokuBlock - Default destructor; clears out the memory used by the block.
* setBlockCellVal - Dereferences an array element and writes a number to that cell.
* getBlockCellVal - Dereferences an array element and returns the number written in that cell.
* setBlockCellNote - Dereferences an array element and sets the boolean in that cell's notes list as 'true'.
* clearBlockCellNote - Dereferences an array element and sets the boolean in that cell's notes list as 'false'.
* getBlockCellNote - Dereferences an array element and returns the boolean value at that cell's notes list index.
* blockValPresent - Checks a 3x3 set for a value, returning whether or not the value appears in any of the cells.
*/
public:
	SudokuBlock();
	~SudokuBlock();
	void setBlockCellVal(int row, int col, int val);
	int getBlockCellVal(int row, int col);
	void setBlockCellNote(int row, int col, int idx);
	void clearBlockCellNote(int row, int col, int idx);
	bool getBlockCellNote(int row, int col, int idx);
	bool blockValPresent(int val);

private:
	SudokuCell* blockCells[3][3];
};

SudokuBlock::SudokuBlock()
{
	// Creates a 3x3 array of blank cells:
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			blockCells[r][c] = new SudokuCell();
		}
	}
}

SudokuBlock::~SudokuBlock()
{
	// Clears the memory from the object:
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			delete blockCells[r][c];
		}
	}
}

void SudokuBlock::setBlockCellVal(int row, int col, int val) {
	blockCells[row][col]->setVal(val);
}

int SudokuBlock::getBlockCellVal(int row, int col) {
	return blockCells[row][col]->getVal();
}

void SudokuBlock::setBlockCellNote(int row, int col, int idx) {
	blockCells[row][col]->setNote(idx);
}

void SudokuBlock::clearBlockCellNote(int row, int col, int idx) {
	blockCells[row][col]->clearNote(idx);
}

bool SudokuBlock::getBlockCellNote(int row, int col, int idx) {
	return blockCells[row][col]->getNote(idx);
}

bool SudokuBlock::blockValPresent(int val) {
	if (val < 0 || val > 9)
		throw std::out_of_range("Value not accepted");
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (getBlockCellVal(row, col) == val) {
				return true;
			}
		}
	}
	
	return false;
}