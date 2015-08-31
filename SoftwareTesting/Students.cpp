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
	for (std::vector<Student>::iterator it = StudentList.begin(); it != StudentList.end(); ++it) {
		/* std::cout << *it; ... */
	}
}

void Students::loadStudents(){
	StudentList = fileIO::loadStudents();
}

void Students::saveStudent(){
	fileIO::saveStudents(StudentList);
}

std::vector<Student> Students::searchStudents(searchBy search_by, std::string searchTerm){

	
	std::string (Student::* func)();

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

std::vector<Student> Students::searchStudents(std::string(Student::* func)(), std::string searchTerm){
	std::vector<Student> to_return;

	for (int i = 0; i < StudentList.size(); ++i){
		if ((StudentList[i].*func)() == searchTerm){
			to_return.push_back(StudentList[i]);
		}
	}

	return to_return;
}

