
#ifndef STUDENTS_H
#define STUDENTS_H
#include "fileIO.h"
#include "student.h"

class Students
{
public:
	Students();
	~Students();
	std::vector<Student> StudentList;

	void addStudent(Student);
	void deleteStudent(Student);
	void loadStudents();
	void saveStudent();

private:


};

#endif 

