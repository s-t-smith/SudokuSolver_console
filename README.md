# SudokuSolver_console
C++ console app to solve sudoku puzzles.

Thought about doing this as an exercise to brush up on some basic coding skills. In an intro class, we made a tic-tac-toe game with basic IO and looping, so this seemed like a good step up from that.

## Assumptions:
To help keep the project focused, I'll be assuming some limitations:
- The sudoku puzzles will be 9x9.
- Starting boards will be arranged by an input text file where the lines represent as cell as such; [row] [column] [digit].

## Process:
Here's how the program will solve a sudoku puzzle:
- A Sudoku board with some cells prepopulated with digits is given.
- Make a pass across each empty cell on the board and check that cell's row, column and 3x3 block, recording possible solutions on that cell's notes.
- After a pass over the notes, make another pass and find cells where only one possibility exists, write that solution to that cell.
- When a solution is written to a cell, make another pass to each empty cell and eliminate solutions invalidated by the previously written solution.
- Repeat until the puzzle is solved.

## Stretch:
If the project reaches a satisfactory state in a reasonable amount of time, I'll add some of these features:

- Variable board size; let the program handle puzzles bigger or smaller than 9x9.
- Branching solve- instead of the brute force note-taking method, I'll change the algorithm to take branches on possibilities and find a solution through trial-and error. This might be a fun way to compare performance between my human method and the computer's method.
- Logging function to show the process the computer takes to solve the puzzle, along with error logging.
