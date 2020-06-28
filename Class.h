#ifndef CLASS_H

#define CLASS_H

////////////////////////////////////////////////
////////////////////班级/////////////////////////
////////////////////////////////////////////////

#include "student.h"

class Class : public basic_info			//班级类
{
public: 
	Class(idType id, const std::string& name)
		: basic_info(id, name, objtype::bClass) {}
	virtual std::string GetObjName() const { return std::string("Class"); }

	//插入学生
	bool InsertStudent(idType studentId); 
	
	//删除学生
	bool DeleteStudent(idType studentId); 

	//获取班级平均分
	virtual scoreType GetAverage() const; 

	const std::set<idType>& GetStudentList() const { return studentList; }

	virtual ~Class() {}

private: 
	std::set<idType> studentList;		//学生列表
}; 




#endif	//#ifndef CLASS_H
