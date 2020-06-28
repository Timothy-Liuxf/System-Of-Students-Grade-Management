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

basic_info::scoreType Class::GetAverage() const
{
	if (studentList.empty()) return 0;										//本班没有学生
	basic_info::scoreType sum = 0; 
	for (std::set<basic_info::idType>::const_iterator itr = studentList.begin();
		itr != studentList.end(); ++itr)
		sum += info.GetStudentList().at(*itr)->GetValid(); 
	return sum / studentList.size(); 
}
