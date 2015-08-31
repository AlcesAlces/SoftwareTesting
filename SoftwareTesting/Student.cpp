#include "Student.h"

Student::Student(){

}

Student::Student(std::string name_in, std::string UID_in, std::string email_in, int essay1Grade_in, int essay2Grade_in, int termProjGrade_in){
	name = name_in;
	UID = UID_in;
	email = email_in;
	essay1Grade = essay1Grade_in;
	essay2Grade = essay2Grade_in,
	termProjGrade = termProjGrade_in;
}

std::string Student::getName(){
	return name;
}

void Student::setName(std::string toSet_name){
	name = toSet_name;
}

std::string Student::getUID(){
	return UID;
}
void Student::setUID(std::string to_set){
	UID = to_set;
}
std::string Student::getEmail(){
	return email;
}
void Student::setEmail(std::string to_set){
	email = to_set;
}
int Student::getEssay1Grade(){
	return essay1Grade;
}
void Student::setEssay1Grade(int to_set){
	essay1Grade = to_set;
}
int Student::getEssay2Grade(){
	return essay2Grade;
}
void Student::setEssay2Grade(int to_set){
	essay2Grade = to_set;
}
int Student::getTermProjGrade(){
	return termProjGrade;
}
void Student::setTermProjGrade(int to_set){
	termProjGrade = to_set;
}

