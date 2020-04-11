//Alba Bella
//CSC 326
//Fall 2018
//This is a "mini" version of VI editor which is a screen-based editor.
//There is a text file called 'editFile.txt' that gets read and displayed in main.
//The user can move the cursor left,down,up,right with 'h','j','k','l'.
//can insert new line with 'I'or new string in a line with 'i'.
//can delete the whole line with 'dd' or delete one char in a line with 'u'.
//can save the file with 'esc:w' and quit with saved changes or without with 'esc:wq' and 'esc:q'.
#include "LinkedList.h"
#include "Command.h"
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"
#include "StackInterface.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Editor.h"
#include <conio.h>
using namespace std;

int main() {
	
	char userInput = NULL;
	Editor myEditor;

	myEditor.readFile("editFile.txt");
	myEditor.displayFile();
	system("CLS");
	myEditor.displayFile();
	
	while (1) {
		int commandTimes = 1;// the commands will be executed one time
		userInput = _getwch();
		//if the char is a number we get the command and execute that number of times
		if (userInput >=  '2' && userInput <= '9') {
			//convert the input from char to int
			commandTimes = userInput - '0';
			userInput = _getwch();
		}
		myEditor.EditorInput(commandTimes, userInput);
		system("CLS");
		myEditor.displayFile();
		
	}
	
	system("pause");
	return 0;
}