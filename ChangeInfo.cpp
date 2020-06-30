
#include "ChangeInfo.h"

void ChangeInfo::Clear()
{
	for (std::map<basic_info::idType, Student*>::const_iterator itr = info.studentList.begin();
		itr != info.studentList.end(); ++itr) delete itr->second;
	info.studentList.clear();

	for (std::map<basic_info::idType, Subject*>::const_iterator itr = info.subjectList.begin();
		itr != info.subjectList.end(); ++itr) delete itr->second;
	info.subjectList.clear();

	for (std::map<basic_info::idType, Class*>::const_iterator itr = info.classList.begin();
		itr != info.classList.end(); ++itr) delete itr->second;
	info.classList.clear();
}

bool ChangeInfo::InsertSubject(basic_info::idType id, const std::string& name, basic_info::scoreType fullScore, int credit)
{
	if (info.subjectList.find(id) != info.subjectList.end()) return false;		//已经有这个ID了
	Subject* tmp = new Subject(id, name, fullScore, credit); 
	info.subjectList.insert(std::make_pair(id, tmp)); 
	return true; 
}

ChangeInfo::operr ChangeInfo::ChangeSubjectID(basic_info::idType srcID, basic_info::idType newID)
{
	if (info.GetSubjectList().find(srcID) == info.GetSubjectList().end()) return operr::no_subject; 
	if (info.GetSubjectList().find(newID) != info.GetSubjectList().end()) return operr::subject_exist; 

	//更改学科列表
	Subject* tmp = info.GetSubjectList().at(srcID); 
	info.subjectList.erase(srcID); 
	tmp->SetID(newID); 
	info.subjectList.insert(std::make_pair(newID, tmp)); 

	//更改学习改学科的学生列表
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = tmp->GetStudentList().begin();
		itr != tmp->GetStudentList().end(); ++itr)
	{
		Student* stu = info.GetStudentList().at(itr->first); 
		stu->DeleteSubject(srcID); 
		stu->InsertSubject(newID, itr->second); 
	}
	return ChangeInfo::operr::success; 
}

bool ChangeInfo::DeleteSubject(basic_info::idType id)
{
	if (info.GetSubjectList().find(id) == info.GetSubjectList().end()) return false;		//不存在该学科
	Subject* sub = info.GetSubjectList().at(id);											//获取该学科指针
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = sub->GetStudentList().begin();
		itr != sub->GetStudentList().end(); ++itr)
	{
		info.GetStudentList().at(itr->first)->DeleteSubject(id);							//删除学生修习的科目
	}
	info.subjectList.erase(id);																//从列表中删除该科目
	delete sub;																				//释放内存空间
	return true; 
}

bool ChangeInfo::InsertClass(basic_info::idType id, const std::string& name)
{
	if (info.classList.find(id) != info.classList.end()) return false;			//已经有这个ID了
	Class* tmp = new Class(id, name); 
	info.classList.insert(std::make_pair(id, tmp)); 
	return true; 
}

ChangeInfo::operr ChangeInfo::ChangeClassID(basic_info::idType srcID, basic_info::idType newID)
{
	if (info.GetClassList().find(srcID) == info.GetClassList().end()) return operr::no_class;
	if (info.GetClassList().find(newID) != info.GetClassList().end()) return operr::class_exist;

	//更改班级列表
	Class* tmp = info.GetClassList().at(srcID);
	info.classList.erase(srcID);
	tmp->SetID(newID);
	info.classList.insert(std::make_pair(newID, tmp));

	//更改在该班级的学生列表
	for (std::set<basic_info::idType>::const_iterator itr = tmp->GetStudentList().begin();
		itr != tmp->GetStudentList().end(); ++itr)
	{
		Student* stu = info.GetStudentList().at(*itr);
		stu->SetClassID(newID); 
	}
	return ChangeInfo::operr::success;
}

ChangeInfo::operr ChangeInfo::DeleteClass(basic_info::idType id)
{
	if (info.GetClassList().find(id) == info.GetClassList().end()) return ChangeInfo::operr::no_class;				//不存在这个班级
	Class* cls = info.GetClassList().at(id);																		//获得指针
	if (!(cls->GetStudentList().empty())) return ChangeInfo::operr::student_exist;									//班级还有学生
	info.classList.erase(id);																						//从列表中清除
	delete cls;																										//释放内存
	return ChangeInfo::operr::success; 
}

bool ChangeInfo::InsertStudent(basic_info::idType id, const std::string& name, Student::genderType gender, basic_info::idType classID)
{
	if (info.studentList.find(id) != info.studentList.end()
		|| info.classList.find(classID) == info.classList.end())
		return false;															//已经有相同ID的学生或没有该ID的班级
	Student* tmp = new Student(id, name, gender, classID); 
	info.studentList.insert(std::make_pair(id, tmp)); 
	info.GetClassList().at(classID)->InsertStudent(id); 
	return true; 
}

bool ChangeInfo::DeleteStudent(basic_info::idType id)
{
	if (info.GetStudentList().find(id) == info.GetStudentList().end()) return false;			//没有这名学生
	Student* stu = info.GetStudentList().at(id);												//获取学生指针
	
	//删除其修习的所有学科记录
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = stu->GetSubjectList().begin();
		itr != stu->GetSubjectList().end(); ++itr)
	{
		info.GetSubjectList().at(itr->first)->DeleteStudent(id); 
	}

	//删除班级中该学生的记录
	info.GetClassList().at(stu->GetClassID())->DeleteStudent(id); 

	info.studentList.erase(id);																	//从列表中删除学生
	delete stu;																					//释放内存
	return true; 
}

ChangeInfo::operr ChangeInfo::AddStudentSubject(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType score)
{
	if (info.GetStudentList().find(studentID) == info.GetStudentList().end()) return operr::no_student;			//不存在这名学生
	if (info.GetSubjectList().find(subjectID) == info.GetSubjectList().end()) return operr::no_subject;			//不存在这门学科
	
	//在学生中插入这门学科
	if (!info.GetStudentList().at(studentID)->InsertSubject(subjectID, score)) return operr::has_studied;		//已经学了这门学科

	//在学科中加入这名学生
	info.GetSubjectList().at(subjectID)->InsertStudent(studentID, score); 
	return operr::success; 
}

ChangeInfo::operr ChangeInfo::DeleteStudentSubject(basic_info::idType studentID, basic_info::idType subjectID)
{
	if (info.GetStudentList().find(studentID) == info.GetStudentList().end()) return ChangeInfo::operr::no_student;			//没有这名学生
	Student* stu = info.GetStudentList().at(studentID); 

	//删除学生的成绩
	if (!(stu->DeleteSubject(subjectID))) return ChangeInfo::operr::no_subject;			//无该学科的成绩
	
	//删除学科处的记录
	info.GetSubjectList().at(subjectID)->DeleteStudent(studentID); 
	return ChangeInfo::operr::success; 
}

ChangeInfo::operr ChangeInfo::ChangeStudentClass(basic_info::idType studentID, basic_info::idType newClassID)
{
	if (info.GetStudentList().find(studentID) == info.GetStudentList().end()) return operr::no_student;			//不存在这名学生
	if (info.GetClassList().find(newClassID) == info.GetClassList().end()) return operr::no_class;				//不存在这个班级
	Student* stu = info.GetStudentList().at(studentID);															//获取学生指针
	info.GetClassList().at(stu->GetClassID())->DeleteStudent(studentID);										//删除原班级
	info.GetClassList().at(newClassID)->InsertStudent(studentID);												//在新班级插入新学生
	stu->SetClassID(newClassID);																				//修改学生的班级ID
	return ChangeInfo::operr::success; 
}

ChangeInfo::operr ChangeInfo::ChangeStudentScore(basic_info::idType studentID, basic_info::idType subjectID, basic_info::scoreType newScore)
{
	if (info.GetStudentList().find(studentID) == info.GetStudentList().end()) return operr::no_student;			//不存在这名学生
	Student* stu = info.GetStudentList().at(studentID);															//获取学生指针

	//更改信息
	if (!(stu->ChangeScore(subjectID, newScore)))																//没有这门学科的成绩
		return operr::no_subject; 
	info.GetSubjectList().at(subjectID)->ChangeScore(studentID, newScore); 
	return ChangeInfo::operr::success; 
}

ChangeInfo::operr ChangeInfo::ChangeStudentID(basic_info::idType srcID, basic_info::idType newID)
{
	if (info.GetStudentList().find(srcID) == info.GetStudentList().end()) return operr::no_student;
	if (info.GetStudentList().find(newID) != info.GetStudentList().end()) return operr::student_exist; 

	//更改学生列表
	Student* stu = info.GetStudentList().at(srcID); 
	info.studentList.erase(srcID); 
	stu->SetID(newID); 
	info.studentList.insert(std::make_pair(newID, stu)); 

	//更改班级列表
	Class* cls = info.GetClassList().at(stu->GetClassID()); 
	cls->DeleteStudent(srcID); 
	cls->InsertStudent(newID); 

	//更改所选课程
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = stu->GetSubjectList().begin();
		itr != stu->GetSubjectList().end(); ++itr)
	{
		Subject* sub = info.GetSubjectList().at(itr->first); 
		sub->DeleteStudent(srcID); 
		sub->InsertStudent(newID, itr->second); 
	}
	return operr::success; 
}

std::list<basic_info*> ChangeInfo::ReadFromFile(const std::string& fileName)
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
	if (fileMode != static_cast<int>(mode) || fin.fail())		//类型不匹配
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
		if (fin.fail())											//读入错误
		{
			fin.clear(); 
			readInfo.push_back(NULL); 
			continue; 
		}
		if (InsertSubject(subID, name, fullScore, credit))	//录入成功
			readInfo.push_back(info.GetSubjectList().at(subID));
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
		if (fin.fail())											//读入错误
		{
			fin.clear(); 
			readInfo.push_back(NULL); 
			continue; 
		}
		if (InsertClass(clsID, name))						//录入成功
			readInfo.push_back(info.GetClassList().at(clsID));
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
			readInfo.push_back(info.GetStudentList().at(stuID));
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
				if (fin.fail())										//读入错误
				{
					fin.clear();
					readInfo.push_back(NULL);
					continue; 
				}
				if (AddStudentSubject(stuID, subID, score) == operr::success)	//录入成功
					readInfo.push_back(info.GetSubjectList().at(subID));
				else readInfo.push_back(NULL);									//录入失败
			}
		}
		else
		{
			size_t j; 
			subNum = subRead.size(); 
			for (j = 0; j < subNum; ++j)
			{
				fin >> score;													//读入学科成绩
				if (fin.fail())														//读取失败
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
						readInfo.push_back(info.GetSubjectList().at(subID));
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

bool ChangeInfo::SaveToFile(const std::string& fileName)
{
	std::ofstream fout(fileName.c_str(), std::ios::out);
	if (!fout) return false;

	//第一行，存储文件类型
	fout << static_cast<int>(mode) << std::endl;

	//写入科目信息
		//第二行，科目数量n
	fout << info.GetSubjectList().size() << std::endl;

	//后面2n行，每两行代表一个科目
	for (std::map<basic_info::idType, Subject*>::const_iterator itr = info.GetSubjectList().begin();
		itr != info.GetSubjectList().end(); ++itr)
	{
		//前一行储存科目名称
		fout << itr->second->GetName() << std::endl;

		//后一行依次储存科目id、满分，学分模式须输出学分数
		fout << itr->second->GetID() << ' ' << itr->second->GetFullScore(); 
		if (mode == modeType::optional) fout << ' ' << itr->second->GetCredit();
		fout << std::endl;
	}


	//下一行，储存班级数k
	fout << info.GetClassList().size() << std::endl;

	//下面2k行，每两行代表一个班级
	for (std::map<basic_info::idType, Class*>::const_iterator itr = info.GetClassList().begin();
		itr != info.GetClassList().end(); ++itr)
	{
		//前一行存储班级名称
		fout << itr->second->GetName() << std::endl;

		//后一行储存班级id
		fout << itr->second->GetID() << std::endl;
	}


	//下一行，储存学生数m
	fout << info.GetStudentList().size() << std::endl;

	//后面3m行，每3行代表一个学生
	for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
		itr != info.GetStudentList().end(); ++itr)
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

