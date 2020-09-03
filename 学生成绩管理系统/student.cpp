#include "student.h"

bool Student::InsertSubject(basic_info::idType subjectId, basic_info::scoreType score)
{
	if (subjectList.find(subjectId) != subjectList.end()) return false;			//已经学了这门课程
	subjectList.insert(std::make_pair(subjectId, score)); 
	return true; 
}

bool Student::ChangeScore(basic_info::idType subjectId, basic_info::scoreType score)
{
	if (subjectList.find(subjectId) == subjectList.end()) return false;			//没学过这门课程
	subjectList[subjectId] = score; 
	return true; 
}

bool Student::DeleteSubject(basic_info::idType subjectId)
{
	if (subjectList.find(subjectId) == subjectList.end()) return false;			//没学过这门课程
	subjectList.erase(subjectId); 
	return true; 
}
