#include "Students.h"


Students::Students()
{
}


Students::~Students()
{
}

Students::Students(std::vector<Student> toAdd)
{
	for each (Student var in toAdd)
	{
		StudentList.push_back(var);
	}
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

	std::string(Student::* func)() const;

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
	if (stud1.getName() == stud2.getName() && stud1.getUID() == stud2.getUID() && stud1.getEmail() == stud2.getEmail() &&
		stud1.getEssay1Grade() == stud2.getEssay1Grade() && stud1.getEssay1Grade() == stud2.getEssay1Grade()
		&& stud1.getTermProjGrade() == stud2.getTermProjGrade()){
		return true;
	}
	else {
		return false;
	}
}

void Students::printAllStudents()
{
	for each (Student var in StudentList)
	{
		std::cout << var.infoToPrint() << std::endl;
	}
}