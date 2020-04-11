//Command.cpp
#include "Command.h"
#include  <iostream>
using namespace std;


Command::Command() { //deafult constructor

}

Command::Command(string inCommand, string inValue) {
	command = inCommand;
	value = inValue;
}

Command::Command(string inCommand) {
	command = inCommand;
}

Command::Command(char inCommand, string inValue, int rowsavePos) {
	inputCommand = inCommand;
	value = inValue;
	rowPos = rowsavePos;

}

void Command::setCommand(string inCommand) {
	command = inCommand;
}

void Command::setValue(string inValue) {
	value = inValue;
}

string Command::getCommand() {
	return command;
}

string Command::getValue() {
	return value;
}

int Command::getrowPos() {
	return rowPos;
}

char Command::getInputCommand(){
	return inputCommand;
}