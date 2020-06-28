#ifndef CHANGE_INFO_H

#define CHANGE_INFO_H

#include <fstream>
#include <list>
#include "Class.h"

class ChangeInfo					//改变信息
{
public:

	enum operr
	{
		success, 
		no_student, 
		no_subject, 
		no_class, 
		has_studied, 
		student_exist, 
		subject_exist, 
		class_exist
	};

	static void Clear();			//清空信息

	//对学科的操作
	static bool InsertSubject(basic_info::idType id, const std::string& name, basic_info::scoreType fullScore, int credit);
	static bool DeleteSubject(basic_info::idType id);
	static operr ChangeSubjectID(basic_info::idType srcID, basic_info::idType newID);

	//对班级的操作
	static bool InsertClass(basic_info::idType id, const std::string& name);
	static bool DeleteClass(basic_info::idType id);
	static operr ChangeClassID(basic_info::idType srcID, basic_info::idType newID);
	
	//对学生的操作
	static bool InsertStudent(basic_info::idType id, const std::string& name, Student::genderType gender, basic_info::idType classID);
	static bool DeleteStudent(basic_info::idType id);
	static operr AddStudentSubject(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType score); 
	static operr ChangeStudentScore(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType newScore);
	static operr ChangeStudentClass(basic_info::idType studentID, basic_info::idType newClassID); 
	static operr ChangeStudentID(basic_info::idType srcID, basic_info::idType newID); 
	
	//关于存档
	static std::list<basic_info*> ReadFromFile(const std::string& fileName);	//存档，返回一个链表，记录读入的对象信息；若有对象读入失败则指针为NULL
	static bool SaveToFile(const std::string& fileName);						//读档		
};


#endif //#ifndef CHANGE_INFO_H
