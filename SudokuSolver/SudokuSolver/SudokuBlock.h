#pragma once

#include "SudokuCell.h"
#include <iostream>
using namespace std;

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
	bool rowValPresent(int row, int val);
	bool colValPresent(int col, int val);
	void printBlock();
	void printRow(int row);

private:
	vector<vector<SudokuCell*>> blockCells;
};

SudokuBlock::SudokuBlock() {
	// Default to 3x3 block:
	blockCells.resize(3);
	for (int r = 0; r < 3; r++) {
		blockCells[r].resize(3);
		for (int c = 0; c < 3; c++) {
			blockCells[r][c] = new SudokuCell();
		}
	}
}

SudokuBlock::SudokuBlock(int size) {
	// Construct an NxN 2D array of cells:
	blockCells.resize(size);
	for (int r = 0; r < size; r++) {
		blockCells[r].resize(size);
		for (int c = 0; c < size; c++) {
			blockCells[r][c] = new SudokuCell();
		}
	}
}

SudokuBlock::~SudokuBlock() {
	for (auto r : blockCells) {
		for (auto c : r) {
			delete c;
		}
	}
}

void SudokuBlock::setBlockCellVal(int row, int col, int val) {
	// Skip invalid ranges:
	if ((row < 0 || row > (int) blockCells.size()) || (col < 0 || col > (int) blockCells.size())) {
		return;
	}
	// Ignore invalid inputs:
	if (val<0 || val>blockCells[row][col]->getSize()) {
		return;
	}
	blockCells[row][col]->setVal(val);
}

int SudokuBlock::getBlockCellVal(int row, int col) {
	// Skip invalid ranges:
	if ((row < 0 || row > (int) blockCells.size()) || (col < 0 || col > (int) blockCells.size())) {
		return -1;
	}
	return blockCells[row][col]->getVal();
}

void SudokuBlock::setBlockCellNote(int row, int col, int idx, bool set) {
	// Skip invalid ranges:
	if ((row<0 || row > (int) blockCells.size()) || (col < 0 || col > (int) blockCells.size())) {
		return;
	}
	blockCells[row][col]->setNote(idx, set);
}

bool SudokuBlock::getBlockCellNote(int row, int col, int idx) {
	// Skip invalid ranges:
	if ((row<0 || row > (int) blockCells.size()) || (col < 0 || col > (int) blockCells.size())) {
		return false;
	}
	return blockCells[row][col]->getNote(idx);
}

bool SudokuBlock::blockValPresent(int val) {
	// Skip invalid ranges:
	if (val < 0 || val > (int) blockCells.size()) {
		return false;
	}
	// If a value is present in a 2D array
	for (auto r : blockCells) {
		for (auto c : r) {
			if (c->getVal() == val)
				return true;
		}
	}
	return false;
}

bool SudokuBlock::rowValPresent(int row, int val) {
	// Skip invalid ranges:
	if (row < 0 || row > (int) blockCells.size()) {
		return false;
	}
	for (int col = 0; col < (int) blockCells.size(); col++) {
		if (blockCells[row][col]->getVal() == val) {
			return true;
		}
	}
	return false;
}

bool SudokuBlock::colValPresent(int col, int val) {
	// Skip invalid ranges:
	if (col < 0 || col > (int) blockCells.size()) {
		return false;
	}
	for (int row = 0; row < (int) blockCells.size(); row++) {
		if (blockCells[row][col]->getVal() == val) {
			return true;
		}
	}
	return false;
}

// Probably only usesful for debugging:
void SudokuBlock::printBlock() {
	for (auto r : blockCells) {
		cout << "|";
		for (auto c : r) {
			cout << c->getVal() << "|";
		}
		cout << endl;
	}
}

// Used for the upper layer'ss print function:
void SudokuBlock::printRow(int row) {
	cout << "|";
	for (int i = 0; i < (int) blockCells.size(); i++) {
		cout << blockCells[row][i]->getVal() << "|";
	}
}