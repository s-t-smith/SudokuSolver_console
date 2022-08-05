#pragma once

class SudokuCell {
private:
	int cellVal;
	bool notes[9];
public:
	SudokuCell(int val);
	void setVal(int val);
	int getVal();
	void setNote(int index);
	bool getNote(int index);
};