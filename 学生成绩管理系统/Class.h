#ifndef CLASS_H

#define CLASS_H

////////////////////////////////////////////
//
//  班级类
//

#include "student.h"

class Class : public obj_base			//班级类
{
public: 
	Class(idType id, const std::string& name)
		: obj_base(id, name, objtype::bClass, "") {}
	virtual std::string GetObjName() const { return std::string("Class"); }

	//插入学生
	bool InsertStudent(idType studentId); 
	
	//删除学生
	bool DeleteStudent(idType studentId); 

	const std::set<idType>& GetStudentList() const { return studentList; }

	virtual ~Class() {}

private: 
	std::set<idType> studentList;		//学生列表
}; 




#endif	//#ifndef CLASS_H
