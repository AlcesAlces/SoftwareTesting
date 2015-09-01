#include "Students.h"


Students::Students()
{
}


Students::~Students()
{
}

void Students::addStudent(Student in_stud){
	StudentList.push_back(in_stud);
}

void Students::deleteStudent(Student out_stud){
	
	std::vector<Student>::iterator itemItr; 
	itemItr = std::find(StudentList.begin(), StudentList.end(), out_stud);
	if (itemItr != StudentList.end()) {
		StudentList.erase(itemItr);
	}
}

void Students::loadStudents(){
	StudentList = fileIO::loadStudents();
}

void Students::saveStudent(){
	fileIO::saveStudents(StudentList);
}

std::vector<Student> Students::searchStudents(searchBy search_by, std::string searchTerm){

	
	std::string (Student::* func)() const;

	switch (search_by){
		case name:
			func = &Student::getName;
			break;
		case ID:
			func = &Student::getUID;
			break;
		case email:
			func = &Student::getEmail;
			break;
		default:
			std::cout << "error in search" << std::endl;
	}

	return searchStudents(func, searchTerm);

}

std::vector<Student> Students::searchStudents(std::string(Student::* func)() const, std::string searchTerm){
	std::vector<Student> to_return;

	for (int i = 0; i < StudentList.size(); ++i){
		if ((StudentList[i].*func)() == searchTerm){
			to_return.push_back(StudentList[i]);
		}
	}

	return to_return;
}

bool operator==(const Student& stud1, const Student& stud2){
	if (stud1.getName() == stud2.getName()){
		return true;
	}
	else {
		return false;
	}
}

