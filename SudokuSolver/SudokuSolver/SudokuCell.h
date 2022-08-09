#pragma once

/*
* This will be the base-most class for the Sudoku Solver.
* A cell will be where a solution digit is written.
* For this implementation, the cell will also be used for making notes for possible solutions.
*/

class SudokuCell {
/*
* Private members:
* cellVal- Where the cell solution can be written. Can be a digit 0..9.
* notes- Where the possible solutions can be recorded. A 'true' value at an index represents a possible solution of <index>+1.
*/
private:
	int cellVal;
	bool notes[9];
/*
* Public functions:
* SudokuCell()- Default constructor; initializes the cell to "0" with all notes 'false'.
* SudokuCell(int val)- Explicit constructor; initializes the cell with the given digit.
* setVal- Records a digit in the cell's cellVal field.
* getVal- Returns the digit recorded in the cell's cellVal field.
* setNote- Marks a possible solution index as 'true'.
* getNote- Returns the solution index requested.
*/
public:
	SudokuCell();
	SudokuCell(int val);
	void setVal(int val);
	int getVal();
	void setNote(int index);
	bool getNote(int index);
};