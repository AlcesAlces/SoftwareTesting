
#ifndef STUDENTS_H
#define STUDENTS_H
#include "fileIO.h"
#include "student.h"

class Students
{
public:
	enum searchBy {name,ID,email};

	Students();
	Students(std::vector<Student>);
	~Students();
	std::vector<Student> StudentList;

	void addStudent(Student);
	void deleteStudent(Student);
	std::vector<Student> searchStudents(searchBy,std::string);
	std::vector<Student> searchStudents(std::string, std::string);
	void printAllStudents();
	void loadStudents();
	void saveStudent();

private:
	std::vector<Student> searchStudents(std::string(Student::*)(), std::string);

};

#endif 

