#include "Students.h"


Students::Students()
{
}

Students::Students(std::vector<Student> studentVector)
{
	for each (Student var in studentVector)
	{
		StudentList.push_back(var);
	}
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

std::vector<Student> Students::searchStudents(std::string search_by_string, std::string searchTerm) {

	searchBy search_by;

	if (search_by_string == "name")
	{
		search_by = name;
}
	else if (search_by_string == "id")
	{
		search_by = ID;
	}
	else if (search_by_string == "email")
	{
		search_by = email;
	}
	else
	{
		std::vector<Student> dummy;
		return dummy;
	}

	std::string(Student::* func)();

std::vector<Student> Students::searchStudents(std::string(Student::* func)(), std::string searchTerm){
	std::vector<Student> to_return;

	for (int i = 0; i < StudentList.size(); ++i){
		if ((StudentList[i].*func)() == searchTerm){
			to_return.push_back(StudentList[i]);
		}
	}

	return to_return;
}

