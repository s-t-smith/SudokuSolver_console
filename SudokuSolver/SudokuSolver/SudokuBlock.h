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
	int getBlockSize();
	void initBlock();
	void printBlock();
	void printRow(int row);

private:
	int blockSize;
	vector<vector<SudokuCell*>> blockCells;
};

SudokuBlock::SudokuBlock() {
	// Default to 3x3 block:
	blockSize = 3;
	initBlock();
}

SudokuBlock::SudokuBlock(int size) {
	blockSize = size;
	// Construct an NxN 2D array of cells:
	initBlock();
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
	if ((row < 0 || row > blockSize) || (col < 0 || col > blockSize)) {
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
	if ((row < 0 || row > blockSize) || (col < 0 || col > blockSize)) {
		return -1;
	}
	return blockCells[row][col]->getVal();
}

void SudokuBlock::setBlockCellNote(int row, int col, int idx, bool set) {
	// Skip invalid ranges:
	if ((row<0 || row > blockSize) || (col < 0 || col > blockSize)) {
		return;
	}
	blockCells[row][col]->setNote(idx, set);
}

bool SudokuBlock::getBlockCellNote(int row, int col, int idx) {
	// Skip invalid ranges:
	if ((row<0 || row > blockSize) || (col < 0 || col > blockSize)) {
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
	if (row < 0 || row > blockSize) {
		return false;
	}
	for (int col = 0; col < blockSize; col++) {
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

int SudokuBlock::getBlockSize() {
	return blockSize;
}

// Constructor helper:
void SudokuBlock::initBlock() {
	blockCells.resize(blockSize);
	for (int r = 0; r < blockSize; r++) {
		blockCells[r].resize(blockSize);
		for (int c = 0; c < blockSize; c++) {
			blockCells[r][c] = new SudokuCell();
		}
	}
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