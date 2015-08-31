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
	Student stud2("sue", "12345", "email", 12, 12, 12);

	for (int i = 0; i < 10; ++i){
		students.addStudent(stud1);
	}
	students.addStudent(stud2);


	
	std::vector<Student> testsearch = students.searchStudents(Students::name, "sue");

	

	students.saveStudent();

	//Students testLoad;
	//testLoad.loadStudents();

	//fileIO::clearDB();

	//testLoad.saveStudent();

	
	return 0;
}

