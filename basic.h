#ifndef BASIC_H

#define BASIC_H

////////////////////////////////////////////////////////////////
/////////////////////////记录基本信息/////////////////////////////
////////////////////////////////////////////////////////////////

#include <string>
#include <set>
#include <map>

class basic_info									//基本信息抽象类
{
public: 

	enum objtype									//表示对象类型
	{
		bStudent,									//学生
		bSubject,									//学科
		bClass										//班级
	}; 


	typedef int idType; 
	typedef double scoreType; 

	//构造函数
	basic_info(idType id, const std::string& name, objtype objType) : id(id), name(name), objType(objType) {}

	//属性
	void SetID(idType newID) { id = newID; }							//更改ID
	idType GetID() const { return id; }									//获取ID
	std::string GetName() const { return name; }						//获取名字
	void SetName(const std::string& newName) { name = newName; }		//更改名字
	objtype GetObjType() const { return objType; }						//获取对象类型

	//获取平均分虚函数
	virtual scoreType GetAverage() const = 0;							//获取平均分
	//比较
	bool operator<(const basic_info& cmp) { return id < cmp.id; }

	//返回代表对象类型的字符串
	virtual std::string GetObjName() const = 0; 

	//析构函数
	virtual ~basic_info() {}

protected: 

	idType id; 
	std::string name; 
	objtype objType; 
}; 


#endif				//#ifndef BASIC_H
