
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <exception>
#include <string>

class Student{
private:
	std::string name;
	int grade;
	std::map<std::time_t, bool> attendance;
	
public:
	std::string getName();
	void setName(std::string);

	int getGrade();
	void setGrade(int);

	std::map<std::time_t, bool> getAttendance();
	void deleteAttendance(std::time_t);
	void addAttendance(std::time_t, bool);
	bool didAttend(std::time_t);
	
	
};
#endif 