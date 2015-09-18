#include "fileIO.h"
#include <string>

//save students into the data base file so that the it can be uploaded to the program later
void fileIO::saveStudents(std::vector<Student> studList){
	std::ofstream myfile;
	myfile.open("Database.txt");

	for (std::vector<Student>::size_type i = 0; i < studList.size()-1; i++) {
		Student stud = studList[i];
		
		myfile << stud.getName() << ", " << stud.getUID() << ", " << stud.getEmail() << ", " << stud.getEssay1Grade() << ", " <<
			stud.getEssay2Grade() << ", " << stud.getTermProjGrade() << "\n";

	}

	myfile.close();
}

// load students into the Students objects 
std::vector<Student> fileIO::loadStudents(){
	std::vector<Student> to_return;
	std::ifstream file("database.txt");
	std::string line;

	while (std::getline(file, line)){
		to_return.push_back(dbEntryToStudent(line));
	}

	return to_return;
}

//clear the database 
void fileIO::clearDB(){
	/* http://www.cplusplus.com/reference/fstream/ofstream/open/ */
	std::ofstream ofs;
	ofs.open("database.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

//database entry to a student object
Student fileIO::dbEntryToStudent(std::string line){
	Student to_return;

	std::vector<std::string> studInfo = split(line, ' ');

	to_return.setName(studInfo[0]);
	to_return.setUID(studInfo[1]);
	to_return.setEmail(studInfo[2]);
	to_return.setEssay1Grade(stoi(studInfo[3]));
	to_return.setEssay2Grade(stoi(studInfo[4]));
	to_return.setTermProjGrade(stoi(studInfo[5]));

	return to_return;
}

//splits string into a vector by the delimiter
//ex hello world split by space = <<hello>,<wolrd>>
std::vector<std::string> fileIO::split(std::string s, char delimiter){
	std::vector<std::string> toReturn;

	int start = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == delimiter)
		{
			std::string toAdd = "";

			for (int j = start; j < i; j++)
			{
				toAdd += s[j];
			}

			toReturn.push_back(toAdd);

			if (i != s.length() - 1)
			{
				start = i + 1;
			}
		}

		else if (i == s.length() - 1)
		{
			std::string toAdd = "";

			for (int j = start; j <= i; j++)
			{
				toAdd += s[j];
			}

			toReturn.push_back(toAdd);
		}
	}

	return toReturn;
}
