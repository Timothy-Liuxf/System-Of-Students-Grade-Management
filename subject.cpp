#include "subject.h"

bool Subject::InsertStudent(basic_info::idType studentId, basic_info::scoreType score)
{
	if (studentList.find(studentId) != studentList.end()) return false;		//已经有这个学生了
	studentList.insert(std::make_pair(studentId, score)); 
	return true; 
}

bool Subject::ChangeScore(basic_info::idType studentId, basic_info::scoreType score)
{
	if (studentList.find(studentId) == studentList.end()) return false;		//没有这个学生
	studentList[studentId] = score; 
	return true; 
}

basic_info::scoreType Subject::GetScore(basic_info::idType studentId) const
{
	if (studentList.find(studentId) == studentList.end()) return -1;		//没有这个学生
	return studentList.at(studentId); 
}

bool Subject::DeleteStudent(basic_info::idType studentId)
{
	if (studentList.find(studentId) == studentList.end()) return false;		//没有这个学生
	studentList.erase(studentId); 
	return true; 
}

