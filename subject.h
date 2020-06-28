
#ifndef SUBJECT_H

#define SUBJECT_H

////////////////////////////////////////////////////
/////////////////////////学科///////////////////////
////////////////////////////////////////////////////

#include "basic.h"

class Subject : public basic_info							//学科类，存放学生成绩
{
public: 

	//学分须大于或等于零
	Subject(idType id, std::string name, scoreType fullScore ,int credit = 1) 
		: basic_info(id, name, objtype::bSubject), fullScore(fullScore >= 0 ? fullScore : 0),credit(credit >= 0 ? credit : 0) {}

	//计算本门课平均分
	virtual scoreType GetAverage() const; 

	//新学生
	bool InsertStudent(idType studentId, scoreType score); 

	//修改学生成绩
	bool ChangeScore(idType studentId, scoreType score); 

	//获取学生成绩，若没有这个学生则返回-1
	scoreType GetScore(idType studentId) const; 

	//删除学生
	bool DeleteStudent(idType studentId); 

	//获取这门课的满分
	scoreType GetFullScore() const { return fullScore; }

	//设置这门课的满分，必须大于或等于零
	bool SetFullScore(basic_info::scoreType newFullScore) { return (fullScore = newFullScore >= 0 ? newFullScore : fullScore) == newFullScore; }

	//获取学分
	int GetCredit() const { return credit; }

	//更改学分，必须大于或等于零
	bool SetCredit(int newCredit) { return (credit = newCredit >= 0 ? newCredit : credit) == newCredit; }

	//获取学生列表
	const std::map<idType, scoreType>& GetStudentList() const { return studentList; }

	virtual std::string GetObjName() const { return std::string("Subject"); }

	virtual ~Subject() {}
private: 
	std::map<idType, scoreType> studentList;		//记录学习这门课的学生id和他们的分数
	scoreType fullScore;							//记录本门课的满分
	int credit;										//记录本门课的学分数
};


#endif		//#ifndef SUBJECT_H