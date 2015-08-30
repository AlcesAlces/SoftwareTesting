#include "fileIO.h"
#include <string>

void fileIO::saveStudents(std::vector<Student> studList){
	//format to store students name,grade,date bool, date bool,.....,date bool
	std::ofstream myfile;
	myfile.open("Database.txt");

	for (std::vector<Student>::size_type i = 0; i != studList.size(); i++) {
		Student stud = studList[i];
		myfile << stud.getName() << "," << stud.getGrade();

		std::map<std::time_t, bool> attend = stud.getAttendance();

		std::map<std::time_t, bool>::iterator it;
		for (it = attend.begin(); it != attend.end(); it++)
		{
			myfile << "," << it->first << ' ' << it->second;
		}
		myfile << "\n";
	}

	myfile.close();
}


std::vector<Student> fileIO::loadStudents(){
	std::vector<Student> to_return;
	std::ifstream file("database.txt");
	std::string line;
	Student newStud;

	while (std::getline(file, line)){
		to_return.push_back(dbEntryToStudent(line));
	}

	return to_return;
}

void fileIO::clearDB(){
	std::ofstream ofs;
	ofs.open("database.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}


Student fileIO::dbEntryToStudent(std::string line){
	Student to_return;

	std::vector<std::string> studInfo = split(line, ",");

	to_return.setName(studInfo[0]);
	to_return.setGrade(stoi(studInfo[1]));
	
	for (int i = 2; i < studInfo.size(); ++i){
		std::vector<std::string> date = split(studInfo[i], " ");
		std::time_t t = stoi(date[0]);
		to_return.addAttendance(t, stob(date[1]));
	}


	return to_return;
}

bool fileIO::stob(std::string s){
	return s != "0";
}

std::vector<std::string> fileIO::split(std::string s, std::string delimiter){
	std::vector<std::string> to_return;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		to_return.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	to_return.push_back(s);
	return to_return;
}

