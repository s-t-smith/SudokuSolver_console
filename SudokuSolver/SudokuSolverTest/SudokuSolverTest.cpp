#include "pch.h"
#include "CppUnitTest.h"
#include "../SudokuSolver/SudokuCell.cpp"
// #include "../SudokuSolver/SudokuBoard.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuSolverTest
{
	TEST_CLASS(SudokuSolverTest)
	{
	public:
		
		TEST_METHOD(CellTest)
		{
			SudokuCell* testCell = new SudokuCell();

			// Test default constructor:
			Assert::AreEqual(0, testCell->getVal());
			for (int i = 0; i < 9; i++) {
				Assert::IsFalse(testCell->getNote(i));
			}

			// Test explicit constructor:
			delete testCell;
			testCell = new SudokuCell(3);
			Assert::AreEqual(3, testCell->getVal());
			for (int i = 0; i < 9; i++) {
				Assert::IsFalse(testCell->getNote(i));
			}

			// Test setVal() for erroneous input:
			Assert::ExpectException(testCell->setVal(12));
			Assert::

			// Test setVal() for valid input:
				
			// Test setNote() for erroneous input:

			// Test setNote() for valid input:

		}

		TEST_METHOD(BoardTest)
		{
		}

		TEST_METHOD(SudokuTest)
		{
		}
	};
}
