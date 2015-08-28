#include "stdafx.h"
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <Windows.h>

enum Command {Add = 0, Remove = 1, Help = 2, Invalid = -1};
//Green, Red
const WORD colors[] =
{
	0x0A, 0x0C
};
HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

Command ParseStringToCommand(std::string input)
{
	//Send the input tolower.
	std::transform(input.begin(), input.end(), input.begin(), tolower);
	
	Command toReturn = Invalid;

	if (input == "add")
	{
		toReturn = Add;
	}
	else if (input == "remove")
	{
		toReturn = Remove;
	}
	else if (input == "?" || input == "help" || input == "plz")
	{
		toReturn = Help;
	}

	return toReturn;
}

void ParseCommand(Command cmd)
{
	if (cmd == Invalid)
	{
		//Angry color
		SetConsoleTextAttribute(hstdout, colors[1]);
		std::cout << "Invalid command.\n";
		SetConsoleTextAttribute(hstdout, colors[0]);
	}
	else if (cmd == Add)
	{
		//Add a student
	}
	else if (cmd == Remove)
	{
		//Remove a student
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTextAttribute(hstdout, colors[0]);
	std::cout << "Welcome to the student catalog thing\n";
	while (true)
	{
		std::cout << "Input a command:\n";
		std::string toPass = "";
		std::cin >> toPass;

		ParseCommand(ParseStringToCommand(toPass));
	}
	return 0;
}