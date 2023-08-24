# SudokuSolver_console
C++ console app to solve sudoku puzzles.

Thought about doing this as an exercise to brush up on some basic coding skills.
In an intro class, we made a tic-tac-toe game with basic IO and looping, so this seemed like a good step up from that.

***
## Assumptions:
To help keep the project focused, I'll be assuming some limitations:
- Puzzles will be based on boards with square dimensions.
- Puzzles will not be made by the user at runtime, rather created from input files.
- Starting boards will be arranged by an input text file where the lines represent a cell.
Each line will be formatted [row] [column] [digit].
***

***
## Process:
Each session uses an array of cells. Each cell has a written value and a lits of possible values.
Here's how the program will solve a sudoku puzzle:
- A Sudoku board with some cells prepopulated with digits is chosen from the available input files.
- Check each written cell to eliminate possibilities.
	- If a digit is written somewhere, all the cells in that row, column and block (subarray) will have their notes for that digit cleared.
- Check each blank cell, writing solutions where the notes hold only one possibility.
	- Solutions will be written when only one note is in the cell, or when no other cells along that row or column share a note of the same value.
- Repeat until the puzzle is solved.
	- Repetitions are limited to keep the program from running off into infinity.
***

***
### Stretch:
Some features I would like to add, but only after the core function is achieved:

- ~~Variable board size; let the program handle puzzles bigger or smaller than 9x9.
	- Already started this with the scalable branch.
- Branching solve: instead of the brute force note-taking method, I'll change the algorithm to take branches on possibilities and find a solution through trial-and error. This might be a fun way to compare performance between my human method and the computer's method.
- Logging function to show the process the computer takes to solve the puzzle, along with error logging.
- GUI- take this out of console space and create a window to show the board while the program works.
- Events; make the solver respond to note conditions instead of iterating over the entire board.