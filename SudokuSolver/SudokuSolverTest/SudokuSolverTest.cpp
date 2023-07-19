#include "pch.h"
#include "CppUnitTest.h"
#include "../SudokuSolver/SudokuCell.h"
#include "../SudokuSolver/SudokuBlock.h"
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
			
			// For some reason, testing on different computers seems to change the working directory, so uncomment the statement that works:
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

		BEGIN_TEST_METHOD_ATTRIBUTE(DefaultConstructor)
			TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()

		BEGIN_TEST_METHOD_ATTRIBUTE(ExplicitConstructor)
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(DefaultConstructor)
		{
			Logger::WriteMessage("Testing class without starting file...\n");
			Sudoku* testGame = new Sudoku();

			// Default board should be 9x9 and all 0s:
			Assert::AreEqual(9, testGame->getBoardSize());
			for (int r = 1; r <= testGame->getBoardSize(); r++) {
				for (int c = 1; c <= testGame->getBoardSize(); c++) {
					Assert::AreEqual(0, testGame->getBoardCellVal(r, c));
				}
			}
			// Default board should not be "complete":
			Assert::IsFalse(testGame->boardSolved());
			
			delete testGame;
		}

		TEST_METHOD(ExplicitConstructor)
		{
			Logger::WriteMessage("Testing class with starting file...\n");
			// Get a path to the test files:

			// For some reason, testing on different computers seems to change the working directory, so uncomment the statement that works:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";

			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			
			// Starting board is not solved:
			Assert::IsFalse(testGame->boardSolved());
			
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
			Assert::IsTrue(testGame->boardSolved());

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

			// For some reason, testing on different computers seems to change the working directory, so uncomment the statement that works:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";

			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			
			// Spot check note settings for populated cells:
			Assert::IsFalse(testGame->getBoardCellNote(6, 2, 3));
			Assert::IsFalse(testGame->getBoardCellNote(9, 6, 4));
			Assert::IsFalse(testGame->getBoardCellNote(9, 8, 7));
			Assert::IsFalse(testGame->getBoardCellNote(5, 4, 1));
			Assert::IsFalse(testGame->getBoardCellNote(3, 7, 3));
			
			// Spot check note settings for blank cells:
			Assert::IsTrue(testGame->getBoardCellNote(6, 5, 7));
			Assert::IsTrue(testGame->getBoardCellNote(9, 1, 1));
			Assert::IsTrue(testGame->getBoardCellNote(6, 9, 8));
			Assert::IsTrue(testGame->getBoardCellNote(1, 7, 3));
			Assert::IsTrue(testGame->getBoardCellNote(3, 3, 8));

			// Test the bulk-clear methods:
			testGame->clearRowNotes(6, 7);
			testGame->clearColNotes(1, 1);
			for (int i = 1; i <= testGame->getBoardSize(); i++) {
				Assert::IsFalse(testGame->getBoardCellNote(i, 1, 1));
				Assert::IsFalse(testGame->getBoardCellNote(6, i, 7));
			}
			testGame->clearBlockNotes(3, 3, 8);
			Assert::IsFalse(testGame->getBoardCellNote(2, 1, 8));
			Assert::IsFalse(testGame->getBoardCellNote(1, 3, 8));

			delete testGame;
		}

		TEST_METHOD(ValCheckTest)
		{
			Logger::WriteMessage("Testing board check methods...\n");

			// For some reason, testing on different computers seems to change the working directory, so uncomment the statement that works:
			std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path().parent_path() += "\\inputFiles";
			// std::filesystem::path filePath = filesystem::current_path().parent_path().parent_path() += "\\inputFiles";

			// Test an unsolved board:
			Sudoku* testGame = new Sudoku(filePath.string() + "\\easy1.txt");
			
			// Test checkRow:
			Assert::IsTrue(testGame->rowValCheck(1, 1));
			Assert::IsTrue(testGame->rowValCheck(9, 4));
			Assert::IsTrue(testGame->rowValCheck(4, 9));
			Assert::IsFalse(testGame->rowValCheck(2, 2));
			Assert::IsFalse(testGame->rowValCheck(1, 7));
			Assert::IsFalse(testGame->rowValCheck(9, 6));

			// Test checkCol:
			Assert::IsTrue(testGame->colValCheck(9, 7));
			Assert::IsTrue(testGame->colValCheck(3, 1));
			Assert::IsTrue(testGame->colValCheck(2, 2));
			Assert::IsFalse(testGame->colValCheck(4, 5));
			Assert::IsFalse(testGame->colValCheck(9, 9));
			Assert::IsFalse(testGame->colValCheck(1, 3));

			// Test checkBlock:
			Assert::IsTrue(testGame->blockValCheck(1, 2, 9));
			Assert::IsTrue(testGame->blockValCheck(2, 4, 5));
			Assert::IsTrue(testGame->blockValCheck(9, 5, 8));
			Assert::IsTrue(testGame->blockValCheck(3, 9, 7));
			Assert::IsTrue(testGame->blockValCheck(2, 7, 3));

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