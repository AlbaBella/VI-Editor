#include "Editor.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <iterator>
#include <vector>
#define ESCAPE 27//define esc value
using namespace std;

void goToXY(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}

void colorText(int value) {
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value);
}

Editor::Editor() {
	mRow = 1;
	mCol = 1;
}
void Editor::readFile(std::string inFile) {
	fillBST();
	string lineGet;
	ifstream file;

	file.open(inFile);
	if (file.fail()) {
		cout << "Error Opening File\n";
		system("pause");
		exit(1);
	}
	int count = 1;
	while (!file.eof()) {
		getline(file, lineGet);
		mList.insert(count, lineGet);
		count++;
	}
	file.close();
}

void Editor::displayFile() {
		int i, j;
		for (i = 1; i < mList.getLength() + 1; i++) {
			string myLine = mList.getEntry(i);
				istringstream streamWords{ myLine };
				vector<string> words{
				istream_iterator<string>(streamWords),
				istream_iterator<string>()
				};
				bool isKeyword;
				for (string currentWord : words) {
					isKeyword = mBST->contains(currentWord);
					if (!isKeyword)
						colorText(FOREGROUND_BLUE | BACKGROUND_BLUE |
							BACKGROUND_GREEN | BACKGROUND_RED | 0X80);  //blue
					else
						colorText(0XF0);

					cout << " "<<currentWord << "";
				}
				cout << endl;
			}
			goToXY(mCol, mRow-1);
}
int Editor::getPosition() const {
	return mCol;
}

int Editor::getRow() const {
	return mRow;
}

void Editor:: setRow(int inLine) {
	mRow = inLine;
}

void Editor::setPosition(int inPosition) {
	mCol = inPosition;
}

void Editor::EditorInput(int commandTimes, char userInput) {
	for (int times = 0; times < commandTimes; times++) {
		//j goes down
		if (userInput == 'j') {
			if (mRow < mList.getLength()) {
				mRow++;
				if (mCol == 0) {
					mCol = 1;
				}
			}
			if (mCol > mList.getEntry(mRow).size()) {
				mCol = mList.getEntry(mRow).size();
			}
		}
		//k goes up
		if (userInput == 'k') {
			if (mRow > 1) {
				mRow--;
				if (mCol == 0) {
					mCol = 1;// used for old version of display
				}
			}
			if (mCol > mList.getEntry(mRow).size()) {
				mCol = mList.getEntry(mRow).size();
			}
		}
		//l goes right
		if (userInput == 'l') {
			if (mCol < mList.getEntry(mRow).size()) {
				mCol++;
			}
		}
		//h goes left
		if (userInput == 'h') {
			if (mCol > 1) {
				mCol--;
			}
		}
		//push current node entry into command stack to store value and command and row position.
		if (userInput == 'u' && !commandStack.isEmpty()) {
			//undo string will be the value that it is put last in commandStack
			string undoValue = commandStack.peek().getValue();
			//undo position will be the row position that it is put last in commandStack 
			int valuePosition = commandStack.peek().getrowPos();
			//the behave of the code will change if there are commands like insert a new line,
			//insert a new char in a line, and delete a char
			if (commandStack.peek().getInputCommand() == 'I') {
				mList.remove(commandStack.peek().getrowPos());
				commandStack.pop();
			}
			else if (commandStack.peek().getInputCommand() == 'x' 
				|| commandStack.peek().getInputCommand() == 'i') {
				commandStack.pop();
				//replace it back to the old one
				mList.replace(valuePosition, undoValue);
			}
			else {
				commandStack.pop();
				mList.insert(valuePosition, undoValue);
			}
		}
		if (userInput == 'd') {
			char usercommandtwo = NULL;
			usercommandtwo = _getwch();
			if (usercommandtwo == 'd')
			{
				if (!mList.isEmpty())//only push if list is not empty
				{
					commandStack.push(Command(userInput, mList.getEntry(mRow), mRow));
					mList.remove(mRow);
					if (mRow > mList.getLength()) {
						mRow--;
					}
				}
			}
		}//end d userinput

		if (userInput == 'x') {
			//if the line is not empty:
			if (mList.getEntry(mRow) != "") {
				commandStack.push(Command(userInput, mList.getEntry(mRow), mRow));
				//erase one single char from the old line
				string mLine = mList.getEntry(mRow).erase(mCol - 1, 1);
				mList.replace(mRow, mLine);//replace the new line with the old one
			}
			//if it is empty just delete the whole line same as delete command 
			else{
				commandStack.push(Command('d', mList.getEntry(mRow), mRow));
				mList.remove(mRow);
				if (mRow > mList.getLength()) {
					mRow--;
				}
			}
		}
		if (userInput == 'i') {
			string NewVal;
			getline(cin, NewVal);

			//if the line isn't blank:
			if (mList.getEntry(mRow) != "") {
				string mLine = mList.getEntry(mRow).insert(mCol - 1, NewVal);
				commandStack.push(Command('i', mList.getEntry(mRow), mRow));
				mList.replace(mRow, mLine);
			}
			//if the line is blank it will behave like 'I' command is prompt
			else {
				commandStack.push(Command('I', NewVal, mRow));
				mList.insert(mRow, NewVal);
			}
		}
		//command input to add a new node into list
		if (userInput == 'I') {
			string NewValue;
			getline(cin, NewValue);
			commandStack.push(Command('I', NewValue, mRow));
			mList.insert(mRow, NewValue);
		}
	}
	if(userInput==ESCAPE){
		//after the esc another char will be needed 
		char userCursor = NULL;
		userCursor = _getch();
		//the colon will bring the cursor at the bottom of the screen
		if (userCursor == ':') {
			//go the bottom of the screen

			int lastrow = mList.getLength();//getLength() will return the last row
			//the length of the last row will return the last colomn
			int lastcolumn = mList.getEntry(lastrow).length();
			
			goToXY(lastcolumn, lastrow); //function call so the cursor will go to that last position

			char secondInput = NULL;
			secondInput = _getch();
			//after the colon the user can press 'w' to write the same file after the changes 
			//or press 'q' to quit without saving any changes

			if (secondInput == 'w') {
				ofstream myFile;
				myFile.open("editFile.txt");
				for (int row = 1; row < mList.getLength() + 1; row++) {
					string mLine = mList.getEntry(row);
					myFile << mLine << endl;
				}
				myFile.close();
				//if the user decides to quit after saving the changes:
				char quit = NULL;
				quit = _getch();
				if (quit == 'q') {
					system("PAUSE");
					exit(1);
				}
			}
			//this is the option to exit without saving any changes
			else if (secondInput == 'q') {
				mList.clear();
				cout << "YOU ARE EXITING WITHOUT SAVING !!"<<endl;
				system("PAUSE");
				exit(1);
			}
		}
	}
}//end getusercommand

void Editor::replace(int pos, string value){
	mList.replace(pos, value);
	
}

void Editor::fillBST() {
	string itemIn;
	ifstream file;
	file.open("keywords.txt");// read keywrods into BST
	if (file.fail()) {
		cout << "Error Opening File\n";
		system("pause");
		exit(1);
	}
	mBST = new BinarySearchTree<string>;
	while (!file.eof()) {
		file >> itemIn;
		mBST->add(itemIn);
	}
	file.close();
}