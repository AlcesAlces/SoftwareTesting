// SoftwareTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileIO.h"
#include "Student.h"
#include "Students.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Students students;

	Student stud1;
	Student stud2;
	std::tm date1 = {0};
	std::tm date2 = {0};

	date1.tm_mon = 4;
	date1.tm_mday = 5;
	date1.tm_year = 115;

	date2.tm_mon = 2;
	date2.tm_mday = 5;
	date2.tm_year = 116;


	stud1.setName("stud 1");
	stud1.setGrade(2);
	stud1.addAttendance(mktime(&date1), true);
	stud1.addAttendance(mktime(&date2), false);

	stud2.setName("stud 2");
	stud2.setGrade(3);
	stud2.addAttendance(mktime(&date2), true);
	stud2.addAttendance(mktime(&date1), false);

	students.addStudent(stud1);
	students.addStudent(stud2);

	//convert time in map to readable time
	std::time_t t = mktime(&date1);
	std::tm* tmt = localtime(&t);

	std::cout << ctime(&t) << std::endl;

	//students.saveStudent();

	Students testLoad;
	testLoad.loadStudents();

	fileIO::clearDB();

	testLoad.saveStudent();

	
	return 0;
}

