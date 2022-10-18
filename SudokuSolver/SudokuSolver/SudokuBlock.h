#pragma once

#include "SudokuCell.h"

/*
* This is an intermediate class intended to help the higher layers organize and dereference a full board array more easily.
*/

class SudokuBlock
{
// This class will be a simple collection of lower-level objects.
	// The functions of those objects will be explosed through this layer's public functions.
public:
	SudokuBlock();
	~SudokuBlock();
	void setBlockCellVal(int row, int col, int val);
	int getBlockCellVal(int row, int col);
	void setBlockCellNote(int row, int col, int idx);
	void clearBlockCellNote(int row, int col, int idx);
	bool getBlockCellNote(int row, int col, int idx);

private:
	SudokuCell* blockCells[3][3];
};

SudokuBlock::SudokuBlock()
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			blockCells[r][c] = new SudokuCell();
		}
	}
}

SudokuBlock::~SudokuBlock()
{
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