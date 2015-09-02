#include "stdafx.h"
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include "Students.h";

Students students;
enum Command {Add = 0, Remove = 1, Search = 2, Help = -2, Invalid = -1};
//Green, Red
const WORD colors[] =
{
	0x0A, 0x0C
};
HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

std::vector<std::string> splitString(std::string toSplit, char delimiter)
{
	std::vector<std::string> toReturn;

	int start = 0;
	for (int i = 0; i < toSplit.length(); i++)
	{
		if (toSplit[i] == delimiter)
		{
			std::string toAdd = "";

			for (int j = start; j < i; j++)
			{
				toAdd += toSplit[j];
			}

			toReturn.push_back(toAdd);
			
			if (i != toSplit.length() - 1)
			{
				start = i+1;
			}
		}

		else if (i == toSplit.length() - 1)
		{
			std::string toAdd = "";

			for (int j = start; j <= i; j++)
			{
				toAdd += toSplit[j];
			}

			toReturn.push_back(toAdd);
		}
	}

	return toReturn;
}

void ParseCommand(Command cmd, std::vector<std::string> payload)
{
	if (cmd == Invalid)
	{
		//Angry color
		SetConsoleTextAttribute(hstdout, colors[1]);
		std::cout << "Invalid command." << std::endl;
		SetConsoleTextAttribute(hstdout, colors[0]);
	}
	else if (cmd == Add)
	{
		//Add a student
		if (payload.size() != 6)
		{
			//bad news throw the user an error.
			SetConsoleTextAttribute(hstdout, colors[1]);
			std::cout << "Command add recieved incorrect # of arguments." << std::endl;
			SetConsoleTextAttribute(hstdout, colors[0]);
		}
		else
		{
			Student toAdd = Student(payload[0], payload[1], payload[2],
				std::stoi(payload[3]), std::stoi(payload[4]), std::stoi(payload[5]));

			std::vector<Student> toCheck = students.searchStudents(students.ID, toAdd.getUID());

			if (toCheck.size() == 0)
			{
				//TODO: Add verification of studen't information length.
				students.addStudent(toAdd);
				students.saveStudent();
				std::cout << toAdd.getName() + " successfully added" << std::endl;
			}
			else
			{
				std::cout << "Student already exists" << std::endl;
			}
		}
	}
	else if (cmd == Remove)
	{
		//Remove a student
		std::vector<Student> toCheck = students.searchStudents(students.ID, payload[0]);

		if (toCheck.size() == 0)
		{
			std::cout << "Student does not exist." << std::endl;
		}
		else
		{
			students.deleteStudent(toCheck[0]);
			students.saveStudent();
			std::cout << "Student deleted successfully" << std::endl;
		}
	}
	else if (cmd == Search)
	{
		if (payload.size() == 0)
		{
			std::cout << "No search parameters recieved" << std::endl;
		}
		else
		{
			std::vector<std::string> commands = splitString(payload[0], '=');

			if (commands.size() != 2)
			{
				SetConsoleTextAttribute(hstdout, colors[1]);
				std::cout << "Search argument recieved invalid. Format should be email=bob@gmail.com." << std::endl;
				SetConsoleTextAttribute(hstdout, colors[0]);
			}

			Students queryList = Students(students.searchStudents(commands[0],commands[1]));

			for (int i = 1; i < payload.size(); i++)
			{
				std::vector<std::string> commands = splitString(payload[i], '=');

				if (commands.size() != 2)
				{
					SetConsoleTextAttribute(hstdout, colors[1]);
					std::cout << "Search argument recieved invalid. Format should be email=bob@gmail.com." << std::endl;
					SetConsoleTextAttribute(hstdout, colors[0]);
				}

				queryList = queryList.searchStudents(commands[0], commands[1]);
			}
			
			queryList.printAllStudents();
		}
	}
	else if (cmd == Help)
	{
		std::cout << "Here are a list of all the example commands: " << std::endl;
		std::cout << "add name,UID,email,firstscore,secondscore,thirdscore" << std::endl;
		std::cout << "remove UID" << std::endl;
		std::cout << "search UID=id,name=bob" << std::endl;
	}
}

void ParseStringToCommand(std::string input)
{

	//For now everything is COMMMA DELIMITED
	std::vector<std::string> split;

	if (input == "?" || input == "help" || input == "plz")
	{
		input = "help";
	}
	else
	{
		//Send the input tolower.
		std::transform(input.begin(), input.end(), input.begin(), tolower);

		//Little bit of preprocessing
		bool hitChar = false;
		std::string toAdd = "";
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == ' ' || input[i] == ',')
			{
				hitChar = true;
				toAdd = input.substr(0, i);
				input = input.substr(i + 1, input.length());
				break;
			}
		}

		split.push_back(toAdd);

		if (hitChar)
		{
			std::vector<std::string> temp = splitString(input, ',');
			for (int i = 0; i < temp.size(); i++)
			{
				split.push_back(temp[i]);
			}
		}

		input = split[0];
	}
	Command toReturn = Invalid;

	if (input == "add")
	{
		toReturn = Add;
	}
	else if (input == "remove")
	{
		toReturn = Remove;
	}
	else if (input == "help")
	{
		toReturn = Help;
	}
	else if (input == "search")
	{
		toReturn = Search;
	}

	std::vector<std::string> toSend;

	for (int i = 1; i < split.size(); i++)
	{
		toSend.push_back(split[i]);
	}

	ParseCommand(toReturn, toSend);
}

int _tmain(int argc, _TCHAR* argv[])
{
	students.loadStudents();
	SetConsoleTextAttribute(hstdout, colors[0]);
	std::cout << "Welcome to the student catalog thing" << std::endl;
	while (true)
	{
		std::cout << "Input a command:" << std::endl;
		std::string toPass = "";
		std::getline(std::cin, toPass);

		ParseStringToCommand(toPass);
	}
	return 0;
}