#pragma once

#include "SudokuCell.h"

/*
* This is an intermediate class intended to help the higher layers organize and dereference a full board array more easily.
*/

class SudokuBlock
{
public:
	SudokuBlock();
	~SudokuBlock();
	void setCellVal(int row, int col, int val);
	int getCellVal(int row, int col);
	void setCellNote(int row, int col, int idx);
	void clearCellNote(int row, int col, int idx);
	bool getCellNote(int row, int col, int idx);

private:
	SudokuCell* blockCells[3][3];
};

SudokuBlock::SudokuBlock()
{
}

SudokuBlock::~SudokuBlock()
{
}

void SudokuBlock::setCellVal(int row, int col, int val) {
	blockCells[row][col]->setVal(val);
}

int SudokuBlock::getCellVal(int row, int col) {
	return blockCells[row][col]->getVal();
}

void SudokuBlock::setCellNote(int row, int col, int idx) {
	blockCells[row][col]->setNote(idx);
}

void SudokuBlock::clearCellNote(int row, int col, int idx) {
	blockCells[row][col]->clearNote(idx);
}

bool SudokuBlock::getCellNote(int row, int col, int idx) {
	return blockCells[row][col]->getNote(idx);
}