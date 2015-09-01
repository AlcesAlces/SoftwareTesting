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

	switch (search_by) {
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

void Students::printAllStudents()
{

	if (StudentList.size() == 0)
	{
		std::cout << "No students in list" << std::endl;
	}

	else
	{
		for each (Student var in StudentList)
		{
			std::string toPrint = var.printInformation();
			std::cout << toPrint << std::endl;
		}
	}
}

