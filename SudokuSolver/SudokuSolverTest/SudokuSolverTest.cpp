#include "pch.h"
#include "CppUnitTest.h"
#include "../SudokuSolver/SudokuCell.h"
#include "../SudokuSolver/SudokuBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuSolverTest
{
	TEST_CLASS(SudokuCellTest)
	{
	public:
		
		SudokuCellTest()
		{
			Logger::WriteMessage("Beginning Sudoku Cell test...");
		}

		~SudokuCellTest()
		{
			Logger::WriteMessage("Completed Sudoku Cell test.");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(DefaultConstructor)
			TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()

		BEGIN_TEST_METHOD_ATTRIBUTE(SetVal)
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(DefaultConstructor)
		{
			Logger::WriteMessage("Testing default constructor...");
			SudokuCell* defaultCell = new SudokuCell();
			Assert::AreEqual(0, defaultCell->getVal());
			int noteSize = defaultCell->getSize();
			for (int i = 0; i < noteSize; i++)
			{
				Assert::IsFalse(defaultCell->getNote(i));
			}
			delete defaultCell;
		}

		TEST_METHOD(ExplicitConstructor)
		{
			Logger::WriteMessage("Testing explicit constructor...");
			SudokuCell* explicitCell = new SudokuCell(5, 9);
			Assert::AreEqual(5, explicitCell->getVal());
			int noteSize = explicitCell->getSize();
			for (int i = 0; i < noteSize; i++)
			{
				Assert::IsFalse(explicitCell->getNote(i));
			}
			delete explicitCell;
			explicitCell = new SudokuCell(3, 16);
			Assert::AreEqual(3, explicitCell->getVal());
			noteSize = explicitCell->getSize();
			for (int i = 0; i < noteSize; i++)
			{
				Assert::IsFalse(explicitCell->getNote(i));
			}
			delete explicitCell;
		}

		TEST_METHOD(SetVal)
		{
			Logger::WriteMessage("Testing setter and getter...");
			SudokuCell* newCell = new SudokuCell(1, 25);
			Assert::AreEqual(1, newCell->getVal());
			Assert::AreEqual(25, newCell->getSize());
			newCell->setVal(3);
			Assert::AreEqual(3, newCell->getVal());
			Assert::AreEqual(25, newCell->getSize());
			delete newCell;
		}

		TEST_METHOD(SetValError)
		{
			SudokuCell* newCell = new SudokuCell();
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setVal(22); });
			Assert::AreEqual(0, newCell->getVal());
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setVal(-4); });
			Assert::AreEqual(0, newCell->getVal());
			delete newCell;
		}

		TEST_METHOD(SetNote)
		{
			Logger::WriteMessage("Testing notes setter and getter...");
			SudokuCell* newCell = new SudokuCell();
			Assert::AreEqual(0, newCell->getVal());
			newCell->setNote(2);
			Assert::IsTrue(newCell->getNote(2));
			delete newCell;
		}

		TEST_METHOD(SetNoteError)
		{
			SudokuCell* newCell = new SudokuCell();
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setNote(-3); });
			for (int i = 0; i < 9; i++)
			{
				Assert::IsFalse(newCell->getNote(i));
			}
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setNote(15); });
			for (int i = 0; i < 9; i++)
			{
				Assert::IsFalse(newCell->getNote(i));
			}
			delete newCell;
		}
	};

	/*TEST_CLASS(SudokuBlockTest)
	{
	public:

		SudokuBlockTest()
		{
			Logger::WriteMessage("No Block test written.");
		}

		// Block not being used for this implementation.
	};*/

	TEST_CLASS(SudokuBoardTest)
	{
	public:

		SudokuBoardTest()
		{
			Logger::WriteMessage("Beginning Sudoku Board test...");
		}

		~SudokuBoardTest()
		{
			Logger::WriteMessage("Completed Sudoku Board test.");
		}

		TEST_METHOD(EmptyBoardTest)
		{
			SudokuBoard* emptyBoard = new SudokuBoard();

			for (int r = 1; r < 10; r++) {
				for (int c = 1; c < 10; c++) {
					Assert::AreEqual(emptyBoard->getCellVal(r, c), 0);
					for (int n = 1; n < 10; n++) {
						Assert::IsFalse(emptyBoard->getCellNote(r, c, n));
					}
				}
			}

			emptyBoard->setCellNote(1, 2, 8);
			Assert::IsTrue(emptyBoard->getCellNote(1, 2, 8));

			emptyBoard->setCellVal(4, 4, 3);
			Assert::ExpectException<std::out_of_range>([&emptyBoard]() {emptyBoard->setCellVal(4, 4, 23); });
			Assert::AreEqual(emptyBoard->getCellVal(4, 4), 3);
			for (int n = 1; n < 10; n++) {
				Assert::IsFalse(emptyBoard->getCellNote(4, 4, n));
			}

			delete emptyBoard;
		}

		TEST_METHOD(StartingBoardTest)
		{
			// need to rewrite this for the new architecture; Sudoku class now builds starting boards.
		}
	};
}
