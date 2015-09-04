#include "stdafx.h"
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Students.h";

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const bool win = true;
#else
static const bool win = false;
#endif

Students students;
enum Command {Add = 0, Remove = 1, Search = 2, Update = 3, Help = -2, Invalid = -1};


void printMessageWithColor(std::string toPrint)
{
	if (win)
	{
		//SetConsoleTextAttribute(hstdout, colors[1]);
		std::cout << toPrint << std::endl;
		//SetConsoleTextAttribute(hstdout, colors[0]);
	}

	else
	{
		std::cout << toPrint << std::endl;
	}
}

void ParseCommand(Command cmd, std::vector<std::string> payload)
{
	if (cmd == Invalid)
	{
		printMessageWithColor("Invalid command.");
	}
	else if (cmd == Add)
	{
		//Add a student
		if (payload.size() != 6)
		{
			//bad news throw the user an error.
			printMessageWithColor("Command add recieved incorrect # of arguments.");
		}
		else
		{
			Student toAdd = Student(payload[0], payload[1], payload[2],
				std::stoi(payload[3]), std::stoi(payload[4]), std::stoi(payload[5]));

			std::vector<Student> toCheck = students.searchStudents(students.ID, toAdd.getUID());

			if (toCheck.size() == 0)
			{
				if (!toAdd.isValidStudent())
				{
					printMessageWithColor("Invalid student attribute.");
					return;
				}

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
			std::cout << "Printing all students:" << std::endl;
			students.printAllStudents();
		}
		else
		{
			std::vector<std::string> commands = fileIO::split(payload[0], '=');

			if (commands.size() != 2)
			{
				printMessageWithColor("Search argument recieved invalid. Format should be email=bob@gmail.com.");
			}

			Students queryList = Students(students.searchStudents(commands[0],commands[1]));

			for (int i = 1; i < payload.size(); i++)
			{
				std::vector<std::string> commands = fileIO::split(payload[i], '=');

				if (commands.size() != 2)
				{
					printMessageWithColor("Search argument recieved invalid. Format should be email=bob@gmail.com.");
				}

				queryList = queryList.searchStudents(commands[0], commands[1]);
			}
			
			queryList.printAllStudents();
		}
	}
	else if (cmd == Update)
	{
		std::vector<Student> tempStudents = students.searchStudents(Students::ID, payload[0]);
		
		for (int i = 1; i < payload.size(); i++)
		{
			std::vector<std::string> commands = fileIO::split(payload[i], '=');
			students.updateInfo(tempStudents[0], commands);
		}

		students.saveStudent();
	}
	else if (cmd == Help)
	{
		std::cout << "Here are a list of all the example commands: " << std::endl;
		std::cout << "add <name>,<UID>,<email>,<firstscore>,<secondscore>,<thirdscore>" << std::endl;
		std::cout << "remove <UID>" << std::endl;
		std::cout << "search UID=<id>,name=<bob>" << std::endl;
		std::cout << "update <UID>,UID=<id>,name=<new name>" << std::endl;
	}
}

void ParseStringToCommand(std::string input)
{

	//For now everything is COMMMA DELIMITED
	std::vector<std::string> split;
	std::string originalInput = input;

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
			std::vector<std::string> temp = fileIO::split(input, ',');
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
	else if (input == "search" || originalInput == "search")
	{
		toReturn = Search;
	}
	else if (input == "update")
	{
		toReturn = Update;
	}

	std::vector<std::string> toSend;

	for (int i = 1; i < split.size(); i++)
	{
		toSend.push_back(split[i]);
	}

	ParseCommand(toReturn, toSend);
}

int _tmain(int argc, char* argv[])
{
	students.loadStudents();
	if (win)
	{
		//SetConsoleTextAttribute(hstdout, colors[0]);
	}

	std::cout << "Welcome to the student catalog thing" << std::endl;
	while (true)
	{
		std::cout << "Input a command:" << std::endl;
		std::string toPass = "";
		std::getline(std::cin, toPass);

		if (toPass == "exit")
		{
			break;
		}

		ParseStringToCommand(toPass);
	}
	return 0;
}