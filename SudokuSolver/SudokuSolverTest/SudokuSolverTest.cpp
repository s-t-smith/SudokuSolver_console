#include "pch.h"
#include "CppUnitTest.h"
#include "../SudokuSolver/SudokuCell.h"
#include "../SudokuSolver/SudokuBoard.h"
#include "../SudokuSolver/Sudoku.h"
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuSolverTest
{
	TEST_CLASS(SudokuCellTest)
	{
	public:
		
		SudokuCellTest()
		{
			Logger::WriteMessage("Beginning Sudoku Cell test...\n");
		}

		~SudokuCellTest()
		{
			Logger::WriteMessage("Completed Sudoku Cell test.\n\n");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(DefaultConstructor)
			TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()

		BEGIN_TEST_METHOD_ATTRIBUTE(SetVal)
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(DefaultConstructor)
		{
			Logger::WriteMessage("Testing default constructor...\n");
			SudokuCell* defaultCell = new SudokuCell();
			// Default cell value is 0:
			Assert::AreEqual(0, defaultCell->getVal());
			// Size defaults to 9:
			int noteSize = defaultCell->getSize();
			Assert::AreEqual(9, noteSize);
			// All notes default to 'true':
			for (int i = 0; i < noteSize; i++)
			{
				Assert::IsTrue(defaultCell->getNote(i));
			}
			delete defaultCell;
		}

		TEST_METHOD(ExplicitConstructor)
		{
			Logger::WriteMessage("Testing explicit constructor...\n");
			SudokuCell* explicitCell = new SudokuCell(5);
			// Cell retains given intial value:
			Assert::AreEqual(5, explicitCell->getVal());
			// Notes list retains given size (default 9):
			int noteSize = explicitCell->getSize();
			Assert::AreEqual(9, noteSize);
			// All notes are written 'false':
			for (int i = 0; i < noteSize; i++)
			{
				Assert::IsFalse(explicitCell->getNote(i));
			}
			delete explicitCell;
			explicitCell = new SudokuCell(3, 16);
			// Cell retains given intial value:
			Assert::AreEqual(3, explicitCell->getVal());
			// Notes list retains given size (default 9):
			noteSize = explicitCell->getSize();
			Assert::AreEqual(16, noteSize);
			// All notes are written 'false':
			for (int i = 0; i < noteSize; i++)
			{
				Assert::IsFalse(explicitCell->getNote(i));
			}
			delete explicitCell;
		}

		TEST_METHOD(SetVal)
		{
			Logger::WriteMessage("Testing setter and getter...\n");
			SudokuCell* newCell = new SudokuCell(1, 25);
			// Check cell value:
			Assert::AreEqual(1, newCell->getVal());
			// Check notes list size:
			Assert::AreEqual(25, newCell->getSize());
			newCell->setVal(3);
			// Check cell value:
			Assert::AreEqual(3, newCell->getVal());
			// Check notes list size:
			Assert::AreEqual(25, newCell->getSize());
			delete newCell;
		}

		TEST_METHOD(SetValError)
		{
			Logger::WriteMessage("Testing setter exceptions...\n");
			SudokuCell* newCell = new SudokuCell();
			// Check setting oversized value:
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setVal(22); });
			Assert::AreEqual(0, newCell->getVal());
			// Check setting vegative value:
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setVal(-4); });
			Assert::AreEqual(0, newCell->getVal());
			delete newCell;
		}

		TEST_METHOD(SetNote)
		{
			Logger::WriteMessage("Testing notes setter and getter...\n");
			// Create default cell:
			SudokuCell* newCell = new SudokuCell();
			Assert::AreEqual(0, newCell->getVal());
			// Check default note, change state, re-check:
			Assert::IsTrue(newCell->getNote(2));
			newCell->clearNote(2);
			Assert::IsFalse(newCell->getNote(2));
			delete newCell;
		}

		TEST_METHOD(SetNoteError)
		{
			Logger::WriteMessage("Testing notes setter exceptions...\n");
			SudokuCell* newCell = new SudokuCell();
			// Check setting negative index:
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setNote(-3); });
			for (int i = 0; i < 9; i++)
			{
				Assert::IsTrue(newCell->getNote(i));
			}
			// Check setting oversized index:
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setNote(15); });
			for (int i = 0; i < 9; i++)
			{
				Assert::IsTrue(newCell->getNote(i));
			}
			delete newCell;
		}
	};

	// Depricated
	/*TEST_CLASS(SudokuBlockTest)
	{
	public:

		SudokuBlockTest()
		{
			Logger::WriteMessage("No Block test written; Blocks depricated for this branch.\n\n");
		}

	};*/

	TEST_CLASS(SudokuBoardTest)
	{
	public:

		SudokuBoardTest()
		{
			Logger::WriteMessage("Beginning Sudoku Board test...\n");
		}

		~SudokuBoardTest()
		{
			Logger::WriteMessage("Completed Sudoku Board test.\n\n");
		}

		TEST_METHOD(EmptyBoardTest)
		{
			SudokuBoard* emptyBoard = new SudokuBoard();

			// Check default board size:
			Assert::AreEqual(9, emptyBoard->getBoardSize());
			// Check default cell values:
			for (int i = 0; i < emptyBoard->getBoardSize(); i++) {
				for (int j = 0; j < emptyBoard->getBoardSize(); j++) {
					// Have to adjust the indexes up one to compensate for the board layer:
					Assert::AreEqual(0, emptyBoard->getCellVal(i+1, j+1));
				}
			}

			delete emptyBoard;
		}

		TEST_METHOD(StartingBoardTest)
		{
			// Get a path to the test files:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";
			SudokuBoard* startingBoard = new SudokuBoard(filePath.string() + "\\easy1.txt");

			// Check board size:
			Assert::AreEqual(9, startingBoard->getBoardSize());
			// Spot-check cell values:
			Assert::AreEqual(4, startingBoard->getCellVal(1, 4));
			Assert::AreEqual(9, startingBoard->getCellVal(3, 6));
			Assert::AreEqual(8, startingBoard->getCellVal(9, 7));

			delete startingBoard;
		}
	};

	TEST_CLASS(SudokuClassTest)
	{
	public:
		SudokuClassTest()
		{
			Logger::WriteMessage("Beginning Sudoku class test...\n");
		}

		~SudokuClassTest()
		{
			Logger::WriteMessage("Completed Sudoku class test.\n\n");
		}

		TEST_METHOD(DefaultConstructor)
		{
			Logger::WriteMessage("Testing class without starting file...\n");
			Sudoku* testGame = new Sudoku();

			// Default board should be 9x9 and all 0s:
			Assert::AreEqual(0, testGame->getBoardCellVal(1, 1));
			Assert::AreEqual(0, testGame->getBoardCellVal(3, 3));
			Assert::AreEqual(0, testGame->getBoardCellVal(9, 9));
			// Assert::ExpectException<std::out_of_range>([&testGame]() {testGame->getBoardCellVal(11, 2); });

			// Default board should not be "complete":
			Assert::IsFalse(testGame->checkGO());
			// Re-checking shouldn't change the state:
			testGame->checkState();
			Assert::IsFalse(testGame->checkGO());

			delete testGame;
		}

		TEST_METHOD(ExplicitConstructor)
		{
			Logger::WriteMessage("Testing class with starting file...\n");
			// Get a path to the test files:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			
			// Starting board is not solved:
			Assert::IsFalse(testGame->checkGO());
			// Re-checking shouldn't change the state:
			testGame->checkState();
			Assert::IsFalse(testGame->checkGO());

			// Spot check board values:
			Assert::AreEqual(1, testGame->getBoardCellVal(1, 2));
			Assert::AreEqual(4, testGame->getBoardCellVal(9, 6));
			Assert::AreEqual(9, testGame->getBoardCellVal(5, 1));

			// Test a solved board:
			delete testGame;
			testGame = new Sudoku(filePath.string() + "\\easy1solved.txt");
			
			// No values should be blank:
			for (int r = 1; r <= testGame->getBoardSize(); r++) {
				for (int c = 1; c <= testGame->getBoardSize(); c++) {
					Assert::AreNotEqual(0, testGame->getBoardCellVal(r, c));
				}
			}

			// Game state is 'solved' (technically just filled out for this):
			testGame->checkState();
			Assert::IsTrue(testGame->checkGO());

			delete testGame;
		}

		// Tested in the ExplicitConstructor method.
		/*TEST_METHOD(CellValTest)
		{
			Logger::WriteMessage("Testing cell access methods...\n");
			// Get a path to the test files:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";
			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
				// To do: spot check cell values.

			delete testGame;
		}*/

		TEST_METHOD(CellNoteTest)
		{
			Logger::WriteMessage("Testing cell notes methods...\n");
			// Get a path to the test files:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			
			// Spot check note settings for populated cells:
			Assert::IsFalse(testGame->getBoardCellNote(6, 2, 3));
			Assert::IsFalse(testGame->getBoardCellNote(9, 2, 3));
			Assert::IsFalse(testGame->getBoardCellNote(9, 8, 7));
			Assert::IsFalse(testGame->getBoardCellNote(1, 8, 7));
			Assert::IsFalse(testGame->getBoardCellNote(3, 6, 2));
			
			// Spot check note settings for blank cells:
			Assert::IsTrue(testGame->getBoardCellNote(6, 7, 5));
			Assert::IsTrue(testGame->getBoardCellNote(9, 1, 1));
			Assert::IsTrue(testGame->getBoardCellNote(9, 6, 8));
			Assert::IsTrue(testGame->getBoardCellNote(1, 3, 3));
			Assert::IsTrue(testGame->getBoardCellNote(3, 8, 8));

			delete testGame;
		}

		TEST_METHOD(ValCheckTest)
		{
			Logger::WriteMessage("Testing board check methods...\n");
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			
			// Test checkRow:
			Assert::IsTrue(testGame->checkRow(1, 1));
			Assert::IsTrue(testGame->checkRow(9, 5));
			Assert::IsTrue(testGame->checkRow(4, 9));
			Assert::IsFalse(testGame->checkRow(2, 2));
			Assert::IsFalse(testGame->checkRow(1, 7));
			Assert::IsFalse(testGame->checkRow(9, 6));

			// Test checkCol:
			Assert::IsTrue(testGame->checkCol(3, 7));
			Assert::IsTrue(testGame->checkCol(8, 1));
			Assert::IsTrue(testGame->checkCol(5, 2));
			Assert::IsFalse(testGame->checkCol(4, 5));
			Assert::IsFalse(testGame->checkCol(9, 9));
			Assert::IsFalse(testGame->checkCol(2, 3));

			// Test checkBlock:

			delete testGame;
		}

		// Tested in the ExplicitConstructor method.
		/*TEST_METHOD(CheckStateTest)
		{
			Logger::WriteMessage("Testing solution check method...\n");
			// Get a path to the test files:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			testGame->checkState();
			Assert::IsFalse(testGame->checkGO());

			// Test a solved board:
			delete testGame;
			testGame = new Sudoku(filePath.string() + "\\easy1solved.txt");
			testGame->checkState();
			Assert::IsTrue(testGame->checkGO());

			delete testGame;
		}*/
	};
}