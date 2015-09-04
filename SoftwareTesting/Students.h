
#ifndef STUDENTS_H
#define STUDENTS_H
#include "fileIO.h"
#include "student.h"
#include <algorithm>
#include <iomanip>

class Students
{
public:
	enum searchBy {name,ID,email};

	Students();
	~Students();
	Students(std::vector<Student>);
	std::vector<Student> StudentList;

	void addStudent(Student);
	void deleteStudent(Student);
	std::vector<Student> searchStudents(searchBy,std::string);
	std::vector<Student> searchStudents(std::string, std::string);
	void loadStudents();
	void saveStudent();
	void printAllStudents();
	void updateInfo(Student, std::vector<std::string>);

private:
	std::vector<Student> searchStudents(std::string(Student::*)() const, std::string);

};


#endif 

