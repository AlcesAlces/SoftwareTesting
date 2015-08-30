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