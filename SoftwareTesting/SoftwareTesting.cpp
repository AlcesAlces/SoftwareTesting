// SoftwareTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileIO.h"
#include "Student.h"
#include "Students.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Students students;


	Student stud1("bill", "12345", "email", 12, 12, 12);
	Student stud2("sue", "1234", "hello", 12, 12, 12);

	for (int i = 0; i < 10; ++i){
		students.addStudent(stud1);
	}
	students.addStudent(stud2);


	
	std::vector<Student> testsearch = students.searchStudents(Students::name, "sue");
	std::vector<Student> testsearch2 = students.searchStudents(Students::email, "hello");
	std::vector<Student> testsearch3 = students.searchStudents(Students::ID, "12345");


	students.deleteStudent(stud2);

	

	students.saveStudent();

	//Students testLoad;
	//testLoad.loadStudents();

	//fileIO::clearDB();

	//testLoad.saveStudent();

	
	return 0;
}

