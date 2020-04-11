//Command.h
#pragma once
#include<iostream>
using namespace std;
class Command {
public:
	Command(); //default constructor
	Command(string,string); 
	Command(string);
	Command(char, string,int);
	void setCommand(string);
	void setValue(string);
	
	string getCommand();
	string getValue();
	int getrowPos();
	char getInputCommand();

private:
	string command;
	string value;
	char inputCommand;
	int rowPos;
};