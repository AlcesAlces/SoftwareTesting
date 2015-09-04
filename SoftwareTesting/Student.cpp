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

std::string Student::getName() const{
	return name;
}

void Student::setName(std::string toSet_name){
	name = toSet_name;
}

std::string Student::getUID() const{
	return UID;
}
void Student::setUID(std::string to_set){
	UID = to_set;
}
std::string Student::getEmail() const{
	return email;
}
void Student::setEmail(std::string to_set){
	email = to_set;
}
int Student::getEssay1Grade() const{
	return essay1Grade;
}
void Student::setEssay1Grade(int to_set){
	essay1Grade = to_set;
}
int Student::getEssay2Grade() const{
	return essay2Grade;
}
void Student::setEssay2Grade(int to_set){
	essay2Grade = to_set;
}
int Student::getTermProjGrade() const{
	return termProjGrade;
}
void Student::setTermProjGrade(int to_set){
	termProjGrade = to_set;
}

std::string Student::infoToPrint()
{
	std::string toReturn = getName() + "," + getUID() + "," + getEmail() + "," + std::to_string(getEssay1Grade()) +
		"," + std::to_string(getEssay2Grade()) + "," + std::to_string(getTermProjGrade());
	return toReturn;
}

bool Student::updateInfo(std::string prop, std::string val)
{
	if (prop == "name")
	{
		setName(val);
	}
	else if (prop == "id" || prop == "uid")
	{
		setUID(val);
	}
	else if (prop == "email")
	{
		setEmail(val);
	}
	else if (prop == "essay1grade")
	{
		setEssay1Grade(std::stoi(val));
	}
	else if (prop == "essay2grade")
	{
		setEssay2Grade(std::stoi(val));
	}
	else if (prop == "termprojgrade")
	{
		setTermProjGrade(std::stoi(val));
	}
	else
	{
		return false;
	}

	return true;
}

bool Student::isValidStudent()
{
	bool valid = true;

	if (getEssay1Grade() > 4 || getEssay1Grade() < 0 || getEssay2Grade() > 4 || getEssay2Grade() < 0 || 
		getTermProjGrade() > 4 || getTermProjGrade() < 0 || getName().size() > 40 || getUID().size() > 10 ||
		getEmail().size() > 40)	
	{
		valid = false;
	}

	return valid;
}