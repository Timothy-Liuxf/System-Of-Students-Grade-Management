#include "Class.h"

bool Class::InsertStudent(basic_info::idType studentId)
{
	if (studentList.find(studentId) != studentList.end()) return false;		//已经有这个学生了
	studentList.insert(studentId); 
	return true; 
}

bool Class::DeleteStudent(basic_info::idType studentId)
{
	if (studentList.find(studentId) == studentList.end()) return false;		//没有这个学生
	studentList.erase(studentId);
	return true; 
}
