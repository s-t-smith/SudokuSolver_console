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
			SudokuCell* explicitCell = new SudokuCell(5, 9);
			// Cell retains given intial value:
			Assert::AreEqual(5, explicitCell->getVal());
			// Notes list retains given size:
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
			newCell->setNote(2, false);
			Assert::IsFalse(newCell->getNote(2));
			delete newCell;
		}

		TEST_METHOD(SetNoteError)
		{
			Logger::WriteMessage("Testing notes setter exceptions...\n");
			SudokuCell* newCell = new SudokuCell();
			// Check setting negative index:
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setNote(-3, true); });
			for (int i = 0; i < 9; i++)
			{
				Assert::IsTrue(newCell->getNote(i));
			}
			// Check setting oversized index:
			Assert::ExpectException<std::out_of_range>([&newCell]() {newCell->setNote(15, false); });
			for (int i = 0; i < 9; i++)
			{
				Assert::IsTrue(newCell->getNote(i));
			}
			delete newCell;
		}
	};

	/* Removed when blocks were depricated (again):
	TEST_CLASS(SudokuBlockTest)
	{
	public:

		SudokuBlockTest()
		{
			Logger::WriteMessage("Beginning Sudoku Block test...\n");
		}
		~SudokuBlockTest()
		{
			Logger::WriteMessage("Completed Sudoku Block test.\n\n");
		}

		TEST_METHOD(ConstructorTest)
		{
			// Reroute stdout:
			streambuf* cout_restore;
			cout_restore = cout.rdbuf();
			stringstream cout_stream;
			cout.rdbuf(cout_stream.rdbuf());
			
			// Default constructor:
			SudokuBlock* testBlock = new SudokuBlock();
			cout << "Default constructor test block:" << endl;
			testBlock->printBlock();
			Logger::WriteMessage(cout_stream.str().c_str());
			Assert::IsFalse(testBlock->getBlockCellVal(0, 0) == 2);
			Assert::AreEqual(testBlock->getBlockCellVal(1, 2), 0);
			Assert::AreEqual(testBlock->getBlockCellVal(4, 0), -1);

			// Flush stream:
			cout_stream.flush();

			// Explicit constructor:
			delete testBlock;
			testBlock = new SudokuBlock(5);
			cout << "Explicit constructor test block:" << endl;
			testBlock->printBlock();
			Logger::WriteMessage(cout_stream.str().c_str());
			Assert::IsFalse(testBlock->getBlockCellVal(1, 4) == 8);
			Assert::AreEqual(testBlock->getBlockCellVal(3, 3), 0);
			Assert::AreEqual(testBlock->getBlockCellVal(-2, 2), -1);

			// Restore stdout:
			cout.rdbuf(cout_restore);
		}

		TEST_METHOD(CellValTest)
		{
			// Rerout stdout:
			streambuf* cout_restore;
			cout_restore = cout.rdbuf();
			stringstream cout_stream;
			cout.rdbuf(cout_stream.rdbuf());
			
			SudokuBlock* littleBlock = new SudokuBlock(2);
			littleBlock->setBlockCellVal(1, 1, 1);
			littleBlock->setBlockCellVal(0, 0, 1);
			littleBlock->setBlockCellVal(0, 1, 2);
			cout << "Set/Get cell value test block:" << endl;
			littleBlock->printBlock();
			Logger::WriteMessage(cout_stream.str().c_str());

			Assert::AreEqual(littleBlock->getBlockCellVal(0, 0), 1);
			Assert::AreNotEqual(littleBlock->getBlockCellVal(1, 1), 3);
			Assert::AreEqual(littleBlock->getBlockCellVal(0, 1), 2);
			Assert::AreNotEqual(littleBlock->getBlockCellVal(1, 0), 2);

			// Restore stdout:
			cout.rdbuf(cout_restore);
		}

		TEST_METHOD(CellNoteTest)
		{
			SudokuBlock* bigBlock = new SudokuBlock(5);
			bigBlock->setBlockCellVal(2, 2, 2);
			bigBlock->setBlockCellVal(3, 3, 3);
			Assert::IsFalse(bigBlock->getBlockCellNote(2, 2, 1));
			Assert::IsTrue(bigBlock->getBlockCellNote(0, 0, 2));

			for (int i = 0; i < 5; i++) {
				if (i % 2 == 0) {
					bigBlock->setBlockCellNote(4, 4, i, false);
				}
			}
			for (int j = 0; j < 5; j++) {
				if (j % 2 == 0) {
					Assert::IsFalse(bigBlock->getBlockCellNote(4, 4, j));
				}
				else {
					Assert::IsTrue(bigBlock->getBlockCellNote(4, 4, j));
				}
			}
		}

	}; */

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
			// Reroute stdout:
			streambuf* cout_restore;
			cout_restore = cout.rdbuf();
			stringstream cout_stream;
			cout.rdbuf(cout_stream.rdbuf());
			
			SudokuBoard* emptyBoard = new SudokuBoard();
			cout << "Default constructor test board:" << endl;
			emptyBoard->printBoard();
			Logger::WriteMessage(cout_stream.str().c_str());

			// Check default board size:
			Assert::AreEqual(9, emptyBoard->getBoardSize());
			// Check default cell values:
			for (int i = 1; i <= emptyBoard->getBoardSize(); i++) {
				for (int j = 1; j <= emptyBoard->getBoardSize(); j++) {
					Assert::AreEqual(0, emptyBoard->getCellVal(i, j));
				}
			}

			delete emptyBoard;
			cout_stream.str("");
			emptyBoard = new SudokuBoard(4);
			cout << "Small board test:" << endl;
			emptyBoard->printBoard();
			Logger::WriteMessage(cout_stream.str().c_str());
			// Check board size:
			Assert::AreEqual(4, emptyBoard->getBoardSize());
			Assert::AreEqual(2, emptyBoard->getBlockSize());

			delete emptyBoard;
			cout_stream.str("");	// Workaround since flush() and str().clear() wouldn't take.
			emptyBoard = new SudokuBoard(25);
			cout << "Big board test:" << endl;
			emptyBoard->printBoard();
			Logger::WriteMessage(cout_stream.str().c_str());
			// Check board size:
			Assert::AreEqual(25, emptyBoard->getBoardSize());
			Assert::AreEqual(5, emptyBoard->getBlockSize());

			// Restore stdout:
			cout.rdbuf(cout_restore);

			delete emptyBoard;
		}

		TEST_METHOD(StartingBoardTest)
		{
			// Reroute stdout:
			streambuf* cout_restore;
			cout_restore = cout.rdbuf();
			stringstream cout_stream;
			cout.rdbuf(cout_stream.rdbuf());
			
			// Get a path to the test files:
			
			// This path will have to be adjusted for the host machine's directory tree:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";
			
			SudokuBoard* startingBoard = new SudokuBoard(filePath.string() + "\\easy1.txt");
			cout << "Board created from file:" << endl;
			startingBoard->printBoard();
			Logger::WriteMessage(cout_stream.str().c_str());

			// Check board size:
			Assert::AreEqual(9, startingBoard->getBoardSize());
			// Spot-check cell values:
			Assert::AreEqual(4, startingBoard->getCellVal(1, 4));
			Assert::AreEqual(9, startingBoard->getCellVal(3, 6));
			Assert::AreEqual(8, startingBoard->getCellVal(9, 7));

			delete startingBoard;
			startingBoard = new SudokuBoard(filePath.string() + "\\smallTest.txt");
			cout_stream.str("");
			cout << "Small board created from file:" << endl;
			startingBoard->printBoard();
			Logger::WriteMessage(cout_stream.str().c_str());

			// Check board size:
			Assert::AreEqual(4, startingBoard->getBoardSize());
			// Spot-check cell values:
			Assert::AreEqual(1, startingBoard->getCellVal(1, 1));
			Assert::AreEqual(3, startingBoard->getCellVal(3, 3));

			delete startingBoard;
			startingBoard = new SudokuBoard(filePath.string() + "\\bigTest.txt");
			cout_stream.str("");
			cout << "Big board created from file:" << endl;
			startingBoard->printBoard();
			Logger::WriteMessage(cout_stream.str().c_str());

			// Check board size:
			Assert::AreEqual(25, startingBoard->getBoardSize());
			// Spot-check cell values:
			Assert::AreEqual(10, startingBoard->getCellVal(10, 10));
			Assert::AreEqual(6, startingBoard->getCellVal(6, 6));
			Assert::AreEqual(2, startingBoard->getCellVal(2, 2));


			// Restore stdout:
			cout.rdbuf(cout_restore);

			delete startingBoard;
		}

		TEST_METHOD(ValueCheckTests)
		{
			// Create small board:
			// This path will have to be adjusted for the host machine's directory tree:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";

			SudokuBoard* testBoard = new SudokuBoard(filePath.string() + "\\smallTest.txt");
			Assert::AreEqual(4, testBoard->getBoardSize());
			Assert::AreEqual(2, testBoard->getBlockSize());

			// Row value check:
			Assert::IsTrue(testBoard->rowValCheck(1, 1));
			Assert::IsFalse(testBoard->rowValCheck(4, 1));
			Assert::IsTrue(testBoard->rowValCheck(3, 3));
			Assert::IsFalse(testBoard->rowValCheck(4, 2));

			// Col value check:
			Assert::IsTrue(testBoard->colValCheck(2, 2));
			Assert::IsFalse(testBoard->colValCheck(2, 3));
			Assert::IsTrue(testBoard->colValCheck(4, 4));
			Assert::IsFalse(testBoard->colValCheck(2, 1));

			// Block value checks:
			delete testBoard;
			testBoard = new SudokuBoard(filePath.string() + "\\blockCheck.txt");
			Assert::IsTrue(testBoard->blockValCheck(2, 2));
			Assert::IsFalse(testBoard->blockValCheck(9, 8));
			Assert::IsTrue(testBoard->blockValCheck(3, 3, 1));
			Assert::IsFalse(testBoard->blockValCheck(7, 8, 4));

			// Create big board:
			delete testBoard;
			testBoard = new SudokuBoard(filePath.string() + "\\bigTest.txt");
			Assert::AreEqual(25, testBoard->getBoardSize());
			Assert::AreEqual(5, testBoard->getBlockSize());

			// Row value checks:
			Assert::IsTrue(testBoard->rowValCheck(3, 3));
			Assert::IsFalse(testBoard->rowValCheck(10, 1));

			// Col value checks:
			Assert::IsTrue(testBoard->colValCheck(12, 12));
			Assert::IsFalse(testBoard->colValCheck(2, 20));

			// Block value checks:
			Assert::IsTrue(testBoard->blockValCheck(7, 9));
			Assert::IsTrue(testBoard->blockValCheck(25, 25));
			Assert::IsTrue(testBoard->blockValCheck(6, 8, 6));
			Assert::IsTrue(testBoard->blockValCheck(19, 16));
			Assert::IsFalse(testBoard->blockValCheck(1, 11));
			Assert::IsFalse(testBoard->blockValCheck(21, 23, 15));

			delete testBoard;
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

		TEST_METHOD(ExplicitConstructor)
		{
			// Test (int) constructor:
			try {
				Sudoku* intGame = new Sudoku(9);
				delete intGame;
				intGame = new Sudoku(10);
			}
			catch (...) {
				Logger::WriteMessage("Sudoku(int) contructor failed.");
			}

			// Test (board) constructor:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			SudokuBoard* testBoard = new SudokuBoard(filePath.string() + "\\smallTest.txt");
			try { Sudoku* testGame = new Sudoku(*testBoard); }
			catch (...) {
				Logger::WriteMessage("Sudoku(board) constructor failed.");
			}

			// Test (string) constructor:
			try { Sudoku* stringGame = new Sudoku(filePath.string() + "\\smallTest_full.txt"); }
			catch (...) {
				Logger::WriteMessage("Sudoku(srting) constructor failed.");
			}
		}

		TEST_METHOD(UpdateTest)
		{
			// Test updateVals method:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			SudokuBoard* testBoard = new SudokuBoard(filePath.string() + "\\smallTest.txt");
			Sudoku* testGame = new Sudoku(*testBoard);
			testGame->updateGameVals();
			Assert::IsFalse(testGame->boardSolved());

			delete testBoard;
			delete testGame;

			testBoard = new SudokuBoard(filePath.string() + "\\smallTest_full.txt");
			testGame = new Sudoku(*testBoard);
			testGame->updateGameVals();
			Assert::IsTrue(testGame->boardSolved());
		}
	};
}