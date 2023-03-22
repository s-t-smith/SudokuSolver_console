# SudokuSolver_console
C++ console app to solve sudoku puzzles.

Thought about doing this as an exercise to brush up on some basic coding skills. In an intro class, we made a tic-tac-toe game with basic IO and looping, so this seemed like a good step up from that.

## Assumptions:
To help keep the project focused, I'll be assuming some limitations:
- The sudoku puzzles will be 9x9.
	- This has been changed; I created a new branch to make a more scalable version that isn't limited to 9x9.
- Starting boards will be arranged by an input text file where the lines represent as cell as such; [row] [column] [digit].

## Process:
Here's how the program will solve a sudoku puzzle:
- A Sudoku board with some cells prepopulated with digits is given.
- Check each written cell and eliminate possibilities.
	- If a digit is written somewhere, all the cells in that row, column and block can have their notes for that digit cleared.
- Check each blank cell, writing solutions where the notes hold only one possibility.
- Repeat until the puzzle is solved.

## Stretch:
Some features I would like to add, but only after the core function is achieved:

- Variable board size; let the program handle puzzles bigger or smaller than 9x9.
	- Already started this with the scalable branch.
- Branching solve- instead of the brute force note-taking method, I'll change the algorithm to take branches on possibilities and find a solution through trial-and error. This might be a fun way to compare performance between my human method and the computer's method.
- Logging function to show the process the computer takes to solve the puzzle, along with error logging.
- GUI- take this out of console space and create a window to show the board while the program works.
