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

	static bool InsertSubject(basic_info::idType id, const std::string& name, basic_info::scoreType fullScore, int credit);		//插入新学科
	static bool DeleteSubject(basic_info::idType id);																			//删除学科
	static operr ChangeSubjectID(basic_info::idType srcID, basic_info::idType newID);											//更改学科ID

	//对班级的操作

	static bool InsertClass(basic_info::idType id, const std::string& name);													//插入新班级
	static operr DeleteClass(basic_info::idType id);																			//删除班级
	static operr ChangeClassID(basic_info::idType srcID, basic_info::idType newID);												//改变班级ID
	
	//对学生的操作

	static bool InsertStudent(basic_info::idType id, const std::string& name, Student::genderType gender, basic_info::idType classID);	//插入新学生
	static bool DeleteStudent(basic_info::idType id);																					//删除学生
	static operr AddStudentSubject(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType score);			//为学生添加新学科
	static operr DeleteStudentSubject(basic_info::idType studentID, basic_info::idType subjectID);										//删除学生学习的某学科成绩
	static operr ChangeStudentScore(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType newScore);		//更改学生分数
	static operr ChangeStudentClass(basic_info::idType studentID, basic_info::idType newClassID);										//更改学生班级
	static operr ChangeStudentID(basic_info::idType srcID, basic_info::idType newID);													//更改学生ID
	
	//关于存档

	//存档，返回一个链表，记录读入的对象信息；若有对象读入失败则指针为NULL；开始读入学生时指针为-1，即0xffffffff
	static std::list<basic_info*> ReadFromFile(const std::string& fileName); 
	//读档
	static bool SaveToFile(const std::string& fileName); 
};


#endif //#ifndef CHANGE_INFO_H
