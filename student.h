#ifndef STUDENT_H

#define STUDENT_H

////////////////////////////////////////////////////////////////
////////////////////////////学生/////////////////////////////////
////////////////////////////////////////////////////////////////

#include "info.h"
#include "subject.h"

class Student : public basic_info						//学生类
{
public:
	enum genderType
	{
		male,
		female
	};

	//构造函数
	Student(idType id, const std::string& name, genderType gender, idType classId)
		: basic_info(id, name, objType), gender(gender), classId(classId) {}

	virtual std::string GetObjName() const { return std::string("Student"); }

	genderType GetGender() const { return gender; }		//获取性别

	//反转性别
	void ReverseGender() { gender = (gender == genderType::male ? genderType::female : genderType::male); }

	//获取班级ID
	idType GetClassID() const { return classId; }

	//设置班级ID
	void SetClassID(idType newClassID) { classId = newClassID; }

	//学习一门新学科
	bool InsertSubject(idType subjectId, scoreType score);

	//改变分数
	bool ChangeScore(idType subjectId, scoreType score);

	//删除学科
	bool DeleteSubject(idType subjectId);

	//获取学科列表
	const std::map<idType, scoreType>& GetSubjectList() const { return subjectList; }

	//计算总分
	scoreType GetSum() const;

	//计算有效分，选修模式下为均绩，必修模式下为总分
	scoreType GetValid() const { return (mode == modeType::optional) ? GetAverage() : GetSum(); }

	//计算均绩
	virtual scoreType GetAverage() const;

	virtual ~Student() {}

protected:
	genderType gender;									//性别
	std::map<idType, scoreType> subjectList;			//记录学科id和成绩
	idType classId;										//记录班级ID
};

 

#endif	//#ifndef STUDENT_H
