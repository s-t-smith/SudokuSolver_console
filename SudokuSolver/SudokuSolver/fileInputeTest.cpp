#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	
	string inputPath;

	cout << "input file:" << endl;
	cin >> inputPath;
	cout << endl;
	
	
	ifstream inputFile(inputPath);

	int row, col, val = 0;

	while (!inputFile.eof()) {
		inputFile >> row;
		inputFile >> col;
		inputFile >> val;

		cout << "row: " << row << endl;
		cout << "col: " << col << endl;
		cout << "val: " << val << endl << endl;
	}

	return 0;
}