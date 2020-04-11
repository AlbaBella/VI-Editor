#pragma once
#include "LinkedList.h"
#include <string>
#include "Command.h"
#include "ArrayStack.h"
#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"
using namespace std;

class Editor {
public:

	Editor();
	void readFile(string);
	void displayFile();
	void EditorInput(int, char);
	int getRow()const;
	void setRow(int);
	void setPosition(int);
	int getPosition()const;
	void replace(int,string);


private:
	int mCol;//Column Position
	int mRow;//Row Position
	LinkedList<string> mList;
	ArrayStack<Command> commandStack;
	BinarySearchTree<string> * mBST;
	void fillBST();
};