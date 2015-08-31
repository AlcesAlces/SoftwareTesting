#include "fileIO.h"
#include <string>

void fileIO::saveStudents(std::vector<Student> studList){
	//format to store students name,grade,date bool, date bool,.....,date bool
	std::ofstream myfile;
	myfile.open("Database.txt");

	for (std::vector<Student>::size_type i = 0; i != studList.size(); i++) {
		Student stud = studList[i];
		
		myfile << stud.getName() << "," << stud.getUID() <<","<< stud.getEmail() << "," << stud.getEssay1Grade() << "," <<
			stud.getEssay2Grade() << "," << stud.getTermProjGrade() << "\n";

	}

	myfile.close();
}


std::vector<Student> fileIO::loadStudents(){
	std::vector<Student> to_return;
	std::ifstream file("database.txt");
	std::string line;

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
	to_return.setUID(studInfo[1]);
	to_return.setEmail(studInfo[2]);
	to_return.setEssay1Grade(stoi(studInfo[3]));
	to_return.setEssay2Grade(stoi(studInfo[4]));
	to_return.setTermProjGrade(stoi(studInfo[5]));

	return to_return;
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

