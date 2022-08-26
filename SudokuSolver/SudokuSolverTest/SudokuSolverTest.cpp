#include "pch.h"
#include "CppUnitTest.h"
#include "../SudokuSolver/SudokuCell.cpp"
// #include "../SudokuSolver/SudokuBoard.cpp"
// #include "../SudokuSolver/Sudoku.cpp"

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
			for (int i = 0; i < 9; i++)
			{
				Assert::IsFalse(defaultCell->getNote(i));
			}
			delete defaultCell;
		}

		TEST_METHOD(ExplicitConstructor)
		{
			Logger::WriteMessage("Testing explicit constructor...");
			SudokuCell* explicitCell = new SudokuCell(5);
			Assert::AreEqual(5, explicitCell->getVal());
			for (int i = 0; i < 9; i++)
			{
				Assert::IsFalse(explicitCell->getNote(i));
			}
			delete explicitCell;
		}

		TEST_METHOD(SetVal)
		{
			Logger::WriteMessage("Testing setter and getter...");
			SudokuCell* newCell = new SudokuCell(1);
			Assert::AreEqual(1, newCell->getVal());
			newCell->setVal(3);
			Assert::AreEqual(3, newCell->getVal());
			delete newCell;
		}

		TEST_METHOD(SetValError)
		{
			SudokuCell* newCell = new SudokuCell();
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setVal(22); });
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
			delete newCell;
		}
	};

	TEST_CLASS(SudokuBoardTest)
	{
		SudokuBoardTest()
		{
			Logger::WriteMessage("No tests for SudokuBoard class yet.");
		}
	};

	TEST_CLASS(SudokuTest)
	{
		SudokuTest()
		{
			Logger::WriteMessage("No tests for Sudoku class yet");
		}
	};
}
