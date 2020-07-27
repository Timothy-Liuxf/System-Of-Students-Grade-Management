
#ifndef INFO_H

#define INFO_H

///////////////////////////////////////////////
//
//  存放信息
//
//

#include <fstream>
#include <map>
#include <list>
#include <queue>
#include "subject.h"
#include "student.h"
#include "Class.h"

class Info																//存放全局信息
{
public: 

	enum operr						//操作错误
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

	enum modeType					//模式
	{
		compulsory,					//必修课模式
		optional					//选课模式
	};

	//构造函数
	Info() : mode(modeType::optional) {}

	//获取列表

	const std::map<basic_info::idType, Student*>& GetStudentList() const { return studentList; }
	const std::map<basic_info::idType, Subject*>& GetSubjectList() const { return subjectList; }
	const std::map<basic_info::idType, Class*>& GetClassList() const { return classList; }

	//获取与设置模式
	modeType GetMode() const { return mode; }
	void SetMode(modeType newMode) { mode = newMode; }

	//清空信息
	void Clear(); 

	//获取分数

	//获取班级均分
	basic_info::scoreType GetClassAverage(basic_info::idType classID) const; 

	//获取学科均分
	basic_info::scoreType GetSubjectAverage(basic_info::idType subjectID) const; 

	//获取学生平均分
	basic_info::scoreType GetStudentAverage(basic_info::idType studentID) const; 
	//获取学生总分
	basic_info::scoreType GetStudentSum(basic_info::idType studentID) const;
	//计算有效分，选修模式下为均绩，必修模式下为总分
	basic_info::scoreType GetStudentValid(basic_info::idType studentID) const
	{
		return (mode == modeType::optional) ? GetStudentAverage(studentID) : GetStudentSum(studentID);
	}

	//获取学生修读的学分
	int GetStudentCredit(basic_info::idType studentID) const;

	//各种操作

	//对学科的操作

	bool InsertSubject(basic_info::idType id, const std::string& name, basic_info::scoreType fullScore, int credit);	//插入新学科
	bool DeleteSubject(basic_info::idType id);																			//删除学科
	operr ChangeSubjectID(basic_info::idType srcID, basic_info::idType newID);											//更改学科ID

	//对班级的操作

	bool InsertClass(basic_info::idType id, const std::string& name);													//插入新班级
	operr DeleteClass(basic_info::idType id);																			//删除班级
	operr ChangeClassID(basic_info::idType srcID, basic_info::idType newID);												//改变班级ID

	//对学生的操作

	bool InsertStudent(basic_info::idType id, const std::string& name, Student::genderType gender, basic_info::idType classID);	//插入新学生
	bool DeleteStudent(basic_info::idType id);																					//删除学生
	operr AddStudentSubject(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType score);			//为学生添加新学科
	operr DeleteStudentSubject(basic_info::idType studentID, basic_info::idType subjectID);										//删除学生学习的某学科成绩
	operr ChangeStudentScore(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType newScore);		//更改学生分数
	operr ChangeStudentClass(basic_info::idType studentID, basic_info::idType newClassID);										//更改学生班级
	operr ChangeStudentID(basic_info::idType srcID, basic_info::idType newID);													//更改学生ID

	//关于存档

	//存档，返回一个链表，记录读入的对象信息；若有对象读入失败则指针为NULL；开始读入学生时指针为-1，即0xffffffff
	std::list<basic_info*> ReadFromFile(const std::string& fileName);

	//读档
	bool SaveToFile(const std::string& fileName);

	//析构函数
	~Info() { Clear(); }

private: 
	std::map<basic_info::idType, Student*> studentList;			//所有学生列表
	std::map<basic_info::idType, Subject*> subjectList;			//所有学科列表
	std::map<basic_info::idType, Class*> classList;				//所有班级列表

	modeType mode;												//信息模式
}; 

#endif	//#ifndef INFO_H
