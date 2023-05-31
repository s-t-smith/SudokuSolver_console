#pragma once

#include "SudokuCell.h"

/*
* This is an intermediate class intended to help the higher layers organize and dereference a full board array.
*/

class SudokuBlock
{
/* 
* TODO: create and document member functions.
*/
public:
	SudokuBlock();
	SudokuBlock(int size);
	~SudokuBlock();
	void setBlockCellVal(int row, int col, int val);
	int getBlockCellVal(int row, int col);
	void setBlockCellNote(int row, int col, int idx, bool set);
	bool getBlockCellNote(int row, int col, int idx);
	bool blockValPresent(int val);
	bool rowValPresent(int val);
	bool colValPresent(int val);
	void printBlock();

private:
	std::vector<std::vector<SudokuCell*>> blockCells;
};

SudokuBlock::SudokuBlock() {}

SudokuBlock::SudokuBlock(int size) {}

SudokuBlock::~SudokuBlock() {}

void SudokuBlock::setBlockCellVal(int row, int col, int val) {}

int SudokuBlock::getBlockCellVal(int row, int col) {}

void SudokuBlock::setBlockCellNote(int row, int col, int idx, bool set) {}

bool SudokuBlock::getBlockCellNote(int row, int col, int idx) {}

bool SudokuBlock::blockValPresent(int val) {}

bool SudokuBlock::rowValPresent(int val) {}

bool SudokuBlock::colValPresent(int val) {}

void SudokuBlock::printBlock() {}