#ifndef FILEIO_H
#define FILEIO_H
#include "student.h"
#include <fstream>
#include <iostream>

static class fileIO {
public:
	static std::vector<Student> loadStudents();
	static void saveStudents(std::vector<Student>);
	static void clearDB();
private:
	static Student dbEntryToStudent(std::string);
	static std::vector<std::string> split(std::string,std::string);
	static bool stob(std::string);

};
#endif