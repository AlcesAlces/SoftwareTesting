#include "Student.h"

std::string Student::getName(){
	return name;
}

void Student::setName(std::string toSet_name){
	name = toSet_name;
}

void Student::addAttendance(std::time_t date, bool didAttend){
	attendance.emplace(date, didAttend);
}

std::map<std::time_t, bool> Student::getAttendance(){
	return attendance;
}

bool Student::didAttend(std::time_t date){
	return attendance.find(date)->second;
}

void Student::setGrade(int to_set){
	grade = to_set;
}

int Student::getGrade(){
	return grade;
}