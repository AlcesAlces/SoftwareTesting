
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
	std::string UID;
	std::string email;
	int essay1Grade;
	int essay2Grade;
	int termProjGrade;
	
	
public:
	Student();
	Student(std::string, std::string, std::string, int, int, int);
	std::string getName();
	void setName(std::string);

	std::string getUID();
	void setUID(std::string);

	std::string getEmail();
	void setEmail(std::string);

	int getEssay1Grade();
	void setEssay1Grade(int);
	
	int getEssay2Grade();
	void setEssay2Grade(int);

	int getTermProjGrade();
	void setTermProjGrade(int);

	
	
	
};
#endif 