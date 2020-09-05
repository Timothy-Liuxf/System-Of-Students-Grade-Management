#include "info.h"

void Info::Clear()
{
	for (std::map<basic_info::idType, Student*>::const_iterator itr = studentList.begin();
		itr != studentList.end(); ++itr) delete itr->second;
	studentList.clear();

	for (std::map<basic_info::idType, Subject*>::const_iterator itr = subjectList.begin();
		itr != subjectList.end(); ++itr) delete itr->second;
	subjectList.clear();

	for (std::map<basic_info::idType, Class*>::const_iterator itr = classList.begin();
		itr != classList.end(); ++itr) delete itr->second;
	classList.clear();
}


basic_info::scoreType Info::GetClassAverage(basic_info::idType classID) const
{
	std::map<basic_info::idType, Class*>::const_iterator itr = classList.find(classID);
	if (itr == classList.end()) return 0;									//没有这个班级
	Class* pClass = itr->second; 
	if (pClass->GetStudentList().empty()) return 0;							//本班没有学生
	basic_info::scoreType sum = 0; 
	for (std::set<basic_info::idType>::const_iterator itr = pClass->GetStudentList().begin();
		itr != pClass->GetStudentList().end(); ++itr)
		sum += GetStudentValid(*itr); 
	return sum / pClass->GetStudentList().size(); 
}

basic_info::scoreType Info::GetSubjectAverage(basic_info::idType subjectID) const
{
	std::map<basic_info::idType, Subject*>::const_iterator itr = subjectList.find(subjectID); 
	if (itr == subjectList.end()) return 0;									//没有这门课程
	Subject* pSubject = itr->second; 
	basic_info::scoreType sum = 0; 
	if (pSubject->GetStudentList().size() == 0) return 0; //没有学生上这门课
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = pSubject->GetStudentList().begin();
		itr != pSubject->GetStudentList().end(); ++itr)
	{
		sum += itr->second; 
	}
	return sum / pSubject->GetStudentList().size();
}

basic_info::scoreType Info::GetStudentAverage(basic_info::idType studentID) const
{
	std::map<basic_info::idType, Student*>::const_iterator itr = studentList.find(studentID);
	if (itr == studentList.end()) return 0;									//没有这个学生
	Student* pStudent = itr->second; 
	if (pStudent->GetSubjectList().empty()) return 0;						//没学过任何课
	basic_info::scoreType sum = 0; 
	int sumCredit = 0; 
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = pStudent->GetSubjectList().begin();
		itr != pStudent->GetSubjectList().end(); ++itr)
	{
		sum += itr->second * subjectList.at(itr->first)->GetCredit(); 
		sumCredit += subjectList.at(itr->first)->GetCredit(); 
	}
	return sumCredit ? sum / sumCredit : 0; 
}

basic_info::scoreType Info::GetStudentSum(basic_info::idType studentID) const
{
	std::map<basic_info::idType, Student*>::const_iterator itr = studentList.find(studentID);
	if (itr == studentList.end()) return 0;									//没有这个学生
	Student* pStudent = itr->second;
	basic_info::scoreType sum = 0;
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = pStudent->GetSubjectList().begin();
		itr != pStudent->GetSubjectList().end(); ++itr)
		sum += itr->second; 
	return sum; 
}

int Info::GetStudentCredit(basic_info::idType studentID) const
{
	std::map<basic_info::idType, Student*>::const_iterator itr = studentList.find(studentID);
	if (itr == studentList.end()) return 0;									//没有这个学生
	Student* pStudent = itr->second;
	if (pStudent->GetSubjectList().empty()) return 0;						//没学过任何课
	int sumCredit = 0;
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = pStudent->GetSubjectList().begin();
		itr != pStudent->GetSubjectList().end(); ++itr)
	{
		sumCredit += subjectList.at(itr->first)->GetCredit();
	}
	return sumCredit; 
}


bool Info::InsertSubject(basic_info::idType id, const std::string& name, basic_info::scoreType fullScore, int credit)
{
	if (subjectList.find(id) != subjectList.end()) return false;			//已经有这个ID了
	Subject* tmp = new Subject(id, name, fullScore, credit);
	subjectList.insert(std::make_pair(id, tmp));
	return true;
}

Info::operr Info::ChangeSubjectID(basic_info::idType srcID, basic_info::idType newID)
{
	if (subjectList.find(srcID) == subjectList.end()) return operr::no_subject;
	if (subjectList.find(newID) != subjectList.end()) return operr::subject_exist;

	//更改课程列表
	Subject* tmp = subjectList.at(srcID);
	subjectList.erase(srcID);
	tmp->SetID(newID);
	subjectList.insert(std::make_pair(newID, tmp));

	//更改学习改课程的学生列表
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = tmp->GetStudentList().begin();
		itr != tmp->GetStudentList().end(); ++itr)
	{
		Student* stu = studentList.at(itr->first);
		stu->DeleteSubject(srcID);
		stu->InsertSubject(newID, itr->second);
	}
	return Info::operr::success;
}

bool Info::DeleteSubject(basic_info::idType id)
{
	if (subjectList.find(id) == subjectList.end()) return false;				//不存在该课程
	Subject* sub = subjectList.at(id);											//获取该课程指针
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = sub->GetStudentList().begin();
		itr != sub->GetStudentList().end(); ++itr)
	{
		studentList.at(itr->first)->DeleteSubject(id);							//删除学生修习的科目
	}
	subjectList.erase(id);														//从列表中删除该科目
	delete sub;																	//释放内存空间
	return true;
}

bool Info::InsertClass(basic_info::idType id, const std::string& name)
{
	if (classList.find(id) != classList.end()) return false;			//已经有这个ID了
	Class* tmp = new Class(id, name);
	classList.insert(std::make_pair(id, tmp));
	return true;
}

Info::operr Info::ChangeClassID(basic_info::idType srcID, basic_info::idType newID)
{
	if (classList.find(srcID) == classList.end()) return operr::no_class;
	if (classList.find(newID) != classList.end()) return operr::class_exist;

	//更改班级列表
	Class* tmp = classList.at(srcID);
	classList.erase(srcID);
	tmp->SetID(newID);
	classList.insert(std::make_pair(newID, tmp));

	//更改在该班级的学生列表
	for (std::set<basic_info::idType>::const_iterator itr = tmp->GetStudentList().begin();
		itr != tmp->GetStudentList().end(); ++itr)
	{
		Student* stu = studentList.at(*itr);
		stu->SetClassID(newID);
	}
	return Info::operr::success;
}

Info::operr Info::DeleteClass(basic_info::idType id)
{
	if (classList.find(id) == classList.end()) return Info::operr::no_class;				//不存在这个班级
	Class* cls = classList.at(id);															//获得指针
	if (!(cls->GetStudentList().empty())) return Info::operr::student_exist;				//班级还有学生
	classList.erase(id);																	//从列表中清除
	delete cls;																				//释放内存
	return Info::operr::success;
}

bool Info::InsertStudent(basic_info::idType id, const std::string& name, Student::genderType gender, basic_info::idType classID)
{
	if (studentList.find(id) != studentList.end()
		|| classList.find(classID) == classList.end())
		return false;															//已经有相同ID的学生或没有该ID的班级
	Student* tmp = new Student(id, name, gender, classID);
	studentList.insert(std::make_pair(id, tmp));
	classList.at(classID)->InsertStudent(id);
	return true;
}

bool Info::DeleteStudent(basic_info::idType id)
{
	if (studentList.find(id) == studentList.end()) return false;				//没有这名学生
	Student* stu = studentList.at(id);											//获取学生指针

	//删除其修习的所有课程记录
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = stu->GetSubjectList().begin();
		itr != stu->GetSubjectList().end(); ++itr)
	{
		subjectList.at(itr->first)->DeleteStudent(id);
	}

	//删除班级中该学生的记录
	classList.at(stu->GetClassID())->DeleteStudent(id);

	studentList.erase(id);																	//从列表中删除学生
	delete stu;																				//释放内存
	return true;
}

Info::operr Info::AddStudentSubject(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType score)
{
	if (studentList.find(studentID) == studentList.end()) return operr::no_student;			//不存在这名学生
	if (subjectList.find(subjectID) == subjectList.end()) return operr::no_subject;			//不存在这门课程

	//在学生中插入这门课程
	if (!studentList.at(studentID)->InsertSubject(subjectID, score)) return operr::has_studied;		//已经学了这门课程

	//在课程中加入这名学生
	subjectList.at(subjectID)->InsertStudent(studentID, score);
	return operr::success;
}

Info::operr Info::DeleteStudentSubject(basic_info::idType studentID, basic_info::idType subjectID)
{
	if (studentList.find(studentID) == studentList.end()) return Info::operr::no_student;			//没有这名学生
	Student* stu = studentList.at(studentID);

	//删除学生的成绩
	if (!(stu->DeleteSubject(subjectID))) return Info::operr::no_subject;					//无该课程的成绩

	//删除课程处的记录
	subjectList.at(subjectID)->DeleteStudent(studentID);
	return Info::operr::success;
}

Info::operr Info::ChangeStudentClass(basic_info::idType studentID, basic_info::idType newClassID)
{
	if (studentList.find(studentID) == studentList.end()) return operr::no_student;			//不存在这名学生
	if (classList.find(newClassID) == classList.end()) return operr::no_class;				//不存在这个班级
	Student* stu = studentList.at(studentID);												//获取学生指针
	classList.at(stu->GetClassID())->DeleteStudent(studentID);								//删除原班级
	classList.at(newClassID)->InsertStudent(studentID);										//在新班级插入新学生
	stu->SetClassID(newClassID);															//修改学生的班级ID
	return Info::operr::success;
}

Info::operr Info::ChangeStudentScore(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType newScore)
{
	if (studentList.find(studentID) == studentList.end()) return operr::no_student;			//不存在这名学生
	Student* stu = studentList.at(studentID);												//获取学生指针

	//更改信息
	if (!(stu->ChangeScore(subjectID, newScore)))											//没有这门课程的成绩
		return operr::no_subject;
	subjectList.at(subjectID)->ChangeScore(studentID, newScore);
	return Info::operr::success;
}

Info::operr Info::ChangeStudentID(basic_info::idType srcID, basic_info::idType newID)
{
	if (studentList.find(srcID) == studentList.end()) return operr::no_student;
	if (studentList.find(newID) != studentList.end()) return operr::student_exist;

	//更改学生列表
	Student* stu = studentList.at(srcID);
	studentList.erase(srcID);
	stu->SetID(newID);
	studentList.insert(std::make_pair(newID, stu));

	//更改班级列表
	Class* cls = classList.at(stu->GetClassID());
	cls->DeleteStudent(srcID);
	cls->InsertStudent(newID);

	//更改所选课程
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = stu->GetSubjectList().begin();
		itr != stu->GetSubjectList().end(); ++itr)
	{
		Subject* sub = subjectList.at(itr->first);
		sub->DeleteStudent(srcID);
		sub->InsertStudent(newID, itr->second);
	}
	return operr::success;
}

std::list<basic_info*> Info::ReadFromFile(const std::string& fileName)
{
	std::list<basic_info*> readInfo;
	std::ifstream fin(fileName.c_str(), std::ios::in);
	if (!fin) return readInfo;					//打开失败，返回空链表
	size_t subNum, clsNum, stuNum;
	std::string name;
	basic_info::idType subID, clsID, stuID;
	basic_info::scoreType fullScore, score;
	int credit, gender;
	int fileMode;
	std::queue<basic_info::idType> subRead;		//必修模式使用，记录录入的科目

	//读入文件类型
	fin >> fileMode;
	if (fileMode != static_cast<int>(mode) || fin.fail())	//类型不匹配
	{
		fin.close(); return readInfo;
	}

	//读入科目数量
	fin >> subNum;
	if (fin.fail()) return readInfo;
	while (fin.get() != '\n');								//换行
	for (size_t i = 0; i < subNum; ++i)
	{
		std::getline(fin, name);							//读入科目名称
		if (mode == modeType::optional)
			fin >> subID >> fullScore >> credit;			//读入科目ID、满分和学分
		else
		{
			fin >> subID >> fullScore;						//读入科目ID、满分
			credit = 1;
		}
		if (fin.fail())										//读入错误
		{
			fin.clear();
			readInfo.push_back(NULL);
			continue;
		}
		if (InsertSubject(subID, name, fullScore, credit))	//录入成功
			readInfo.push_back(subjectList.at(subID));
		else readInfo.push_back(NULL);						//科目冲突，录入失败
		if (mode == modeType::compulsory) subRead.push(subID);
		while (fin.get() != '\n');							//换行
	}

	//读入班级数
	fin >> clsNum;
	if (fin.fail()) return readInfo;
	while (fin.get() != '\n');								//换行
	for (size_t i = 0; i < clsNum; ++i)
	{
		std::getline(fin, name);							//读入班级名字
		fin >> clsID;										//读入班级ID
		if (fin.fail())										//读入错误
		{
			fin.clear();
			readInfo.push_back(NULL);
			continue;
		}
		if (InsertClass(clsID, name))						//录入成功
			readInfo.push_back(classList.at(clsID));
		else readInfo.push_back(NULL);						//录入失败
		while (fin.get() != '\n');							//换行
	}

	readInfo.push_back((basic_info*)-1);					//开始录入学生

	//录入学生数
	fin >> stuNum;
	if (fin.fail()) return readInfo;
	while (fin.get() != '\n');								//换行
	for (size_t i = 0; i < stuNum; ++i)
	{
		std::getline(fin, name);							//读入学生姓名
		fin >> stuID >> gender >> clsID;					//读入学生ID、性别和班级ID
		if (!fin)											//读入错误
		{
			fin.clear();
			readInfo.push_back(NULL);
			continue;
		}
		while (fin.get() != '\n');							//换行

		//录入成功
		if (InsertStudent(stuID, name, static_cast<Student::genderType>(gender), clsID))
			readInfo.push_back(studentList.at(stuID));
		else readInfo.push_back(NULL);						//录入失败

		//读入课程门数
		fin >> subNum;
		if (fin.fail())											//读入失败
		{
			fin.clear();
			continue;
		}

		if (mode == modeType::optional)
		{

			for (size_t i = 0; i < subNum; ++i)					//录入课程
			{
				fin >> subID >> score;
				if (fin.fail())									//读入错误
				{
					fin.clear();
					readInfo.push_back(NULL);
					continue;
				}
				if (AddStudentSubject(stuID, subID, score) == operr::success)	//录入成功
					readInfo.push_back(subjectList.at(subID));
				else readInfo.push_back(NULL);									//录入失败
			}
		}
		else
		{
			size_t j;
			subNum = subRead.size();
			for (j = 0; j < subNum; ++j)
			{
				fin >> score;													//读入课程成绩
				if (fin.fail())													//读取失败
				{
					fin.clear();
					for (size_t k = j; k < subNum; ++k)
					{
						readInfo.push_back(NULL);
						subID = subRead.front();
						AddStudentSubject(stuID, subID, 0);
						subRead.pop();
						subRead.push(subID);
					}
					break;
				}

				else
				{
					subID = subRead.front();
					if (AddStudentSubject(stuID, subID, score) == operr::success)
						readInfo.push_back(subjectList.at(subID));
					else readInfo.push_back(NULL);
					subRead.pop();
					subRead.push(subID);
				}
			}
			if (j < subNum) continue;
		}
		while (fin.get() != '\n');											//换行
	}
	fin.close();
	return readInfo;
}

bool Info::SaveToFile(const std::string& fileName)
{
	std::ofstream fout(fileName.c_str(), std::ios::out);
	if (!fout) return false;

	//第一行，存储文件类型
	fout << static_cast<int>(mode) << std::endl;

	//写入科目信息
	//第二行，科目数量n
	fout << subjectList.size() << std::endl;

	//后面2n行，每两行代表一个科目
	for (std::map<basic_info::idType, Subject*>::const_iterator itr = subjectList.begin();
		itr != subjectList.end(); ++itr)
	{
		//前一行储存科目名称
		fout << itr->second->GetName() << std::endl;

		//后一行依次储存科目id、满分，学分模式须输出学分数
		fout << itr->second->GetID() << ' ' << itr->second->GetFullScore();
		if (mode == modeType::optional) fout << ' ' << itr->second->GetCredit();
		fout << std::endl;
	}


	//下一行，储存班级数k
	fout << classList.size() << std::endl;

	//下面2k行，每两行代表一个班级
	for (std::map<basic_info::idType, Class*>::const_iterator itr = classList.begin();
		itr != classList.end(); ++itr)
	{
		//前一行存储班级名称
		fout << itr->second->GetName() << std::endl;

		//后一行储存班级id
		fout << itr->second->GetID() << std::endl;
	}


	//下一行，储存学生数m
	fout << studentList.size() << std::endl;

	//后面3m行，每3行代表一个学生
	for (std::map<basic_info::idType, Student*>::const_iterator itr = studentList.begin();
		itr != studentList.end(); ++itr)
	{
		//第一行，记录学生姓名
		fout << itr->second->GetName() << std::endl;

		//第二行，依次记录学生的id、性别和班级id
		fout << itr->second->GetID() << ' ' << static_cast<int>(itr->second->GetGender()) << ' ' << itr->second->GetClassID() << std::endl;

		//第三行第一个数字记录学生修读的课程门数
		fout << itr->second->GetSubjectList().size();

		//后面分别记录每门课程的id和成绩，必修模式不须输出id
		for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr1 = itr->second->GetSubjectList().begin();
			itr1 != itr->second->GetSubjectList().end(); ++itr1)
		{
			if (mode == modeType::optional) fout << ' ' << itr1->first;
			fout << ' ' << itr1->second;
		}
		fout << std::endl;
	}


	return true;
}

