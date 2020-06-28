
#ifndef INFO_H

#define INFO_H

///////////////////////////////////////////////
///////////////////存放信息/////////////////////
///////////////////////////////////////////////

#include <map>
#include "basic.h"

class Student; 
class Subject; 
class Class; 

class Info																//存放全局信息
{
public: 
	const std::map<basic_info::idType, Student*>& GetStudentList() const { return studentList; }
	const std::map<basic_info::idType, Subject*>& GetSubjectList() const { return subjectList; }
	const std::map<basic_info::idType, Class*>& GetClassList() const { return classList; }

	friend class ChangeInfo; 
private: 
	std::map<basic_info::idType, Student*> studentList;			//所有学生列表
	std::map<basic_info::idType, Subject*> subjectList;			//所有学科列表
	std::map<basic_info::idType, Class*> classList;				//所有班级列表
}; 

extern Info info; 

enum modeType					//模式
{
	compulsory,					//必修课模式
	optional					//选课模式
}; 

extern modeType mode; 

#endif	//#ifndef INFO_H
