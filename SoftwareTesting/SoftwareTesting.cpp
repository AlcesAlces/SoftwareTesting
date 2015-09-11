#include "stdafx.h"
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include "Students.h";


Students students;
enum Command {Add = 0, Remove = 1, Search = 2, Update = 3, Help = -2, Invalid = -1};

// print a message
void printMessage(std::string toPrint)
{
		std::cout << toPrint << std::endl;
}

//this function takes the command from the cmd into commands that the program knows
void ParseCommand(Command cmd, std::vector<std::string> payload)
{
	if (cmd == Invalid)
	{
		printMessage("Invalid command.");
	}
	//adds a student
	else if (cmd == Add)
	{
		//Add a student
		if (payload.size() != 6)
		{
			//bad news throw the user an error.
			printMessage("Command add recieved incorrect # of arguments.");
		}
		else
		{
			//constuct the student
			Student toAdd = Student(payload[0], payload[1], payload[2],
				std::stoi(payload[3]), std::stoi(payload[4]), std::stoi(payload[5]));

			std::vector<Student> toCheck = students.searchStudents(students.ID, toAdd.getUID());

			//make sure that id dosent exsist
			if (toCheck.size() == 0)
			{
				//make sure the student is valid
				if (!toAdd.isValidStudent())
				{
					printMessage("Invalid student attribute.");
					return;
				}

				//add
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

	//remove a student
	else if (cmd == Remove)
	{
		//see if student exsists
		std::vector<Student> toCheck = students.searchStudents(students.ID, payload[0]);
		
		//see if student exsist
		if (toCheck.size() == 0)
		{
			std::cout << "Student does not exist." << std::endl;
		}
		else
		{
			//delete student
			students.deleteStudent(toCheck[0]);
			students.saveStudent();
			std::cout << "Student deleted successfully" << std::endl;
		}
	}

	//search for student
	else if (cmd == Search)
	{
		//make sure there are arguments 
		if (payload.size() == 0)
		{
			std::cout << "Printing all students:" << std::endl;
			students.printAllStudents();
		}
		else
		{
			//slit the payload
			std::vector<std::string> commands = fileIO::split(payload[0], '=');

			//make sure the format  is correct
			if (commands.size() != 2)
			{
				printMessage("Search argument recieved invalid. Format should be email=bob@gmail.com.");
			}

			Students queryList = Students(students.searchStudents(commands[0],commands[1]));

			//iterate through rest of the arguments
			for (int i = 1; i < payload.size(); i++)
			{
				std::vector<std::string> commands = fileIO::split(payload[i], '=');

				if (commands.size() != 2)
				{
					printMessage("Search argument recieved invalid. Format should be email=bob@gmail.com.");
				}

				queryList = queryList.searchStudents(commands[0], commands[1]);
			}
			
			queryList.printAllStudents();
		}
	}
	//update the student
	else if (cmd == Update)
	{
		//search for the student
		std::vector<Student> tempStudents = students.searchStudents(Students::ID, payload[0]);
		
		//for each argument update that one
		for (int i = 1; i < payload.size(); i++)
		{
			std::vector<std::string> commands = fileIO::split(payload[i], '=');
			students.updateInfo(tempStudents[0], commands);
		}

		students.saveStudent();
	}
	//you need help so print it
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

		//find the the main command add, remove etc.
		//then splits the command and arugument
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
			//splits aguments
			std::vector<std::string> temp = fileIO::split(input, ',');
			for (int i = 0; i < temp.size(); i++)
			{
				split.push_back(temp[i]);
			}
		}

		input = split[0];
	}

	//default set it to invalid
	Command toReturn = Invalid;

	//take command and turn it into an enum
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