#include "ui.h"

std::streamsize UI::nameLength = 25; 
std::streamsize UI::idLength = 15; 
std::streamsize UI::scoreLength = 8; 

HANDLE hConsoleOutPut; 

void UI::StartProcedure()
{
	system("cls");
	SET_CONSOLE_MAIN_COLOR(); 
	hConsoleOutPut = GetStdHandle(STD_OUTPUT_HANDLE); 
	std::cout << "欢迎使用学生信息管理系统！" << std::endl;
}

void UI::EndProcedure()
{
	ChangeInfo::Clear(); 
	system("cls");
	std::cout << "感谢您的使用" << std::endl;
	system("pause");
}

bool UI::ChooseMode()
{
	char buf = 0; 
	while (true)
	{
		std::cout << "请输入您要使用的模式：" << std::endl << "A.必修模式（适用于义务教育阶段和部分高级中学）\nB.学分模式（适用于部分学分制高中以及高等学校）\nC.关于...\nD.退出程序" << std::endl;
		std::cin >> buf; 
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (buf)
		{
		case 'a': case 'A':
			mode = modeType::compulsory;
			return true;
		case 'b': case'B':
			mode = modeType::optional;
			return true;
		case 'c': case 'C':
			std::cout << std::endl << separator << std::endl << std::endl << about << std::endl << std::endl << separator << std::endl << std::endl;
			break;
		case 'd': case 'D':
			return false;
		default:
			SET_TEXT_WARNING(); 
			std::cout << "输入非法！" << std::endl;
			SET_TEXT_NORMAL(); 
		}
	}
}

void UI::OptionalSystem()
{
	system("cls");
	while (true)
	{
		std::cout << "当前：学生成绩管理系统选修模式" << std::endl;
		std::cout << "A.返回上一级\nB.显示当前的所有学科\nC.输出所有学生成绩\nD.输出某学科学生成绩\nE.输出某班级学生成绩\nF.输出所有班级\nG.添加\nH.更改\nI.查找学生成绩\nJ.删除\nK.读取存档（添加至当前成绩库）\nL.保存...\nM.清空所有数据" << std::endl;
		char buf = 0;
		std::cin >> buf;
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		switch (buf)
		{
		case 'A': case'a':
			SET_TEXT_WARNING(); 
			std::cout << "返回上一级会使数据全部丢失，请务必确认您的数据已经保存，您确定要继续吗? (Y/n): " << std::flush; 
			buf = 0;
			while (true)
			{
				std::cin >> buf; 
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				switch (buf)
				{
				case 'Y': case 'y': case 'N': case 'n': 
					break; 
				default: 
					std::cout << "输入非法! 返回上一级会使得数据全部丢失，你确定吗? (Y/n): " << std::flush; 
					continue; 
				}
				break; 
			}
			SET_TEXT_NORMAL();
			if (buf == 'Y' || buf == 'y')
			{
				ChangeInfo::Clear(); 
				return; 
			}
			break; 
		case 'B': case 'b':
			PrintSubject(); 
			break; 
		case 'C': case'c': 
			std::cout << "是否按成绩排名?(Y/n)" << std::flush; 
			while (true)
			{
				buf = 0; 
				std::cin >> buf; 
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				if (buf == 'Y' || buf == 'y') { PrintStudent(true); break; }
				else if (buf == 'N' || buf == 'n') { PrintStudent(false); break; }
				else
				{
					SET_TEXT_WARNING(); std::cout << "输入非法！是否按成绩排名?(Y/n)" << std::flush; SET_TEXT_NORMAL(); 
				}
			}
			break; 
		case 'D': case 'd': 
		{
			basic_info::idType subjectID; 
			std::cout << "请输入该学科的ID: " << std::flush; 
			while (!(std::cin >> subjectID))
			{
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				SET_TEXT_WARNING();
				std::cout << "输入非法，请重新输入该学科的ID: " << std::flush; 
				SET_TEXT_NORMAL(); 
			}
			std::cout << "是否按成绩排名?(Y/n)" << std::flush;
			while (true)
			{
				buf = 0; 
				std::cin >> buf;
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (buf == 'Y' || buf == 'y') { PrintSubjectStudent(subjectID, true); break; }
				else if (buf == 'N' || buf == 'n') { PrintSubjectStudent(subjectID, false); break; }
				else
				{
					SET_TEXT_WARNING(); std::cout << "输入非法！是否按成绩排名?(Y/n)" << std::flush; SET_TEXT_NORMAL();
				}
			}
			break;
		}
		case 'E': case 'e': 
		{
			basic_info::idType classID;
			std::cout << "请输入该班级的ID: " << std::flush;
			while (!(std::cin >> classID))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				SET_TEXT_WARNING();
				std::cout << "输入非法，请重新输入！" << std::endl;
				SET_TEXT_NORMAL();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "是否按成绩排名?(Y/n)" << std::flush;
			while (true)
			{
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (buf == 'Y' || buf == 'y') { PrintClassStudent(classID, true); break; }
				else if (buf == 'N' || buf == 'n') { PrintClassStudent(classID, false); break; }
				else
				{
					SET_TEXT_WARNING(); std::cout << "输入非法！是否按成绩排名?(Y/n)" << std::flush; SET_TEXT_NORMAL();
				}
			}
			break;
		}
		case 'F': case 'f': 
		{
			PrintClass(); 
			break; 
		}
		case 'G': case 'g': 
		{
			std::cout << "请选择: A.返回上一级\tB.添加新学科\tC.添加新班级\tD.添加新学生\tE.给已存在的学生添加课程" << std::endl; 
			while (true)
			{
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a': 
					break; 
				case 'B': case 'b': 
				{
					addNewSubject: 
					basic_info::idType id; 
					basic_info::scoreType fullScore; 
					int credit; 
					std::string name; 
					std::cout << "请输入添加的新学科的ID: " << std::flush;
					while (!(std::cin >> id) || info.GetSubjectList().find(id) != info.GetSubjectList().end())
					{
						SET_TEXT_WARNING();
						if(std::cin) std::cout << "此班级ID已经被占用！请输入添加的新学科的ID: " << std::flush; 
						else std::cout << "输入非法！请输入添加的新学科的ID: " << std::flush; 
						SET_TEXT_NORMAL(); 
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					std::cout << "请输入添加的新学科的名字: " << std::flush; 
					std::getline(std::cin, name); 
					std::cout << "请分别输入添加的新学科的满分数和学分数: " << std::endl; 
					while (!(std::cin >> fullScore >> credit))
					{
						std::cin.clear(); 
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
						SET_TEXT_WARNING();
						std::cout << "输入非法！请分别输入添加的新学科的满分数和学分数: " << std::endl; 
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					if (ChangeInfo::InsertSubject(id, name, fullScore, credit))
					{
						SET_TEXT_SUCCESS();
						std::cout << "添加新学科成功！" << std::endl;
						SET_TEXT_NORMAL();
					}
					else
					{
						SET_TEXT_WARNING();
						std::cout << "添加失败！未知错误！" << std::endl; 
						SET_TEXT_NORMAL();
					}
					std::cout << "是否继续添加?(Y/n): " << std::flush; 
					buf = 0; 
					std::cin >> buf; 
					std::cin.clear(); 
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					if (buf == 'Y' || buf == 'y') goto addNewSubject; 
					break; 
				}
				case 'C': case'c': 
				{
					addNewClass: 
					basic_info::idType id;
					std::string name;
					std::cout << "请输入添加的新班级的ID: " << std::flush; 
					while (!(std::cin >> id) || info.GetClassList().find(id) != info.GetClassList().end())
					{
						SET_TEXT_WARNING();
						if(std::cin)
							std::cout << "此班级ID已经被占用！请输入添加的新班级的ID: " << std::flush; 
						else std::cout << "输入非法！请输入添加的新班级的ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入添加的新班级的名字: " << std::flush;
					std::getline(std::cin, name);
					if (ChangeInfo::InsertClass(id, name))
					{
						SET_TEXT_SUCCESS(); std::cout << "添加新班级成功！" << std::endl; SET_TEXT_NORMAL(); 
					}
					else
					{
						SET_TEXT_WARNING(); std::cout << "添加失败！未知错误！" << std::endl; SET_TEXT_NORMAL(); 
					}
					std::cout << "是否继续添加?(Y/n): " << std::flush;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto addNewClass;
					break; 
				}
				case 'D': case'd': 
				{
					addNewStudent: 
					basic_info::idType id, classID;
					std::string name;
					Student::genderType gender = Student::genderType::male; 
					std::cout << "请输入添加的新学生的ID: " << std::flush;
					while (!(std::cin >> id) || info.GetStudentList().find(id) != info.GetStudentList().end())
					{
						SET_TEXT_WARNING(); 
						if (std::cin)
							std::cout << "此学生ID已经被占用！请输入添加的新班级的ID: " << std::flush; 
						else std::cout << "输入非法！请输入添加的新学生的ID: " << std::flush;
						SET_TEXT_NORMAL(); 
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入添加的新学生的名字: " << std::flush;
					std::getline(std::cin, name);
					std::cout << "请输入学生的性别(m/f: m-male, f-female): " << std::flush; 
					buf = 0; 
					while(true)
					{
						std::cin >> buf; 
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
						switch (buf)
						{
						case 'M': case'm': 
							gender = Student::genderType::male; 
							break; 
						case 'F': case'f': 
							gender = Student::genderType::female; 
							break; 
						default: 
							SET_TEXT_WARNING(); 
							std::cout << "输入非法！请输入学生的性别(m/f: m-male, f-female): " << std::flush; 
							SET_TEXT_NORMAL(); 
							continue; 
						}
						break; 
					}; 
					std::cout << "请输入该学生所属班级的ID: " << std::flush; 
					while (!(std::cin >> classID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING(); 
						std::cout << "输入非法！请输入该学生所属班级的ID: " << std::flush;
						SET_TEXT_NORMAL(); 
					}
					if (ChangeInfo::InsertStudent(id, name, gender, classID))
					{
						SET_TEXT_SUCCESS(); std::cout << "添加新学生成功！" << std::endl; SET_TEXT_NORMAL();
					}
					else
					{
						SET_TEXT_WARNING(); std::cout << "添加失败！不存在此班级！" << std::endl; SET_TEXT_NORMAL(); 
					}
					std::cout << "是否继续添加?(Y/n): " << std::flush;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto addNewStudent;
					break; 
				}
				case 'E': case 'e': 
				{
					addNewStudentSubject: 
					basic_info::idType studentID, subjectID; 
					basic_info::scoreType score; 
					std::cout << "请依次输入学生的ID、学科的ID和学科的分数: " << std::endl; 
					while (true)
					{
						std::cin >> studentID >> subjectID >> score; 
						if (std::cin.fail())
						{
							SET_TEXT_WARNING(); 
							std::cout << "输入非法！请重新输入学生的ID、学科的ID和学科的分数: " << std::endl; 
							SET_TEXT_NORMAL(); 
							std::cin.clear(); 
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
							continue; 
						}
						switch (ChangeInfo::AddStudentSubject(studentID, subjectID, score))
						{
						case ChangeInfo::operr::success: 
							SET_TEXT_SUCCESS(); 
							std::cout << "操作成功！" << std::endl; 
							SET_TEXT_NORMAL(); 
							break; 
						case ChangeInfo::operr::has_studied: 
							SET_TEXT_WARNING(); 
							std::cout << "该学生已经有了这门课程的成绩" << std::endl; 
							SET_TEXT_NORMAL(); 
							break; 
						case ChangeInfo::operr::no_student: 
							SET_TEXT_WARNING();
							std::cout << "不存在这名学生" << std::endl;
							SET_TEXT_NORMAL();
							break; 
						case ChangeInfo::operr::no_subject: 
							SET_TEXT_WARNING();
							std::cout << "不存在这门学科" << std::endl;
							SET_TEXT_NORMAL();
							break; 
						}
						break; 
					}; 
					std::cout << "是否继续添加?(Y/n): " << std::flush;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto addNewStudentSubject;
					break; 
				}
				default: 
					SET_TEXT_WARNING(); 
					std::cout << "输入非法！" << std::endl; 
					SET_TEXT_NORMAL();
					continue; 
				}
				break; 
			}
			break; 
		}
		case 'H': case 'h': 
		{
			std::cout << "请选择: A.返回上一级\tB.更改学科信息\tC.更改班级信息\tD.更改学生信息" << std::endl; 
			buf = 0;
			std::cin >> buf;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (buf)
			{
			case 'A': case 'a':
				break;
			case 'B': case 'b': 
				std::cout << "请选择：A.更改学科ID\tB.更改学科名称\tC.修改学科满分\tD.修改学科学分\tE.取消" << std::endl; 
				buf = 0; 
				std::cin >> buf; 
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				switch (buf)
				{
				case 'A': case 'a': 
				{
					basic_info::idType srcID, newID; 
					std::cout << "请依次输入学科原ID和新ID: " << std::endl; 
					while (!(std::cin >> srcID >> newID))
					{
						std::cin.clear(); 
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
						SET_TEXT_WARNING();
						std::cout << "输入非法，请重新输入学科原ID和新ID: " << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeSubjectID(srcID, newID))
					{
					case ChangeInfo::operr::success: 
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break; 
					case ChangeInfo::operr::no_subject: 
						SET_TEXT_WARNING();
						std::cout << "该学科不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break; 
					case ChangeInfo::operr::subject_exist: 
						SET_TEXT_WARNING();
						std::cout << "新ID已被占用，修改失败！" << std::endl;
						SET_TEXT_NORMAL(); 
						break; 
					}
					break;
				}
				case 'B': case 'b': 
				{
					basic_info::idType id; 
					std::string name; 
					std::cout << "请输入要修改名称的学科ID: " << std::flush; 
					while (!(std::cin >> id) || info.GetSubjectList().find(id) == info.GetSubjectList().end())
					{
						SET_TEXT_WARNING(); 
						if (std::cin) std::cout << "该学科不存在，请重新输入要修改名称的学科ID: " << std::flush;
						else std::cout << "输入非法，请重新输入要修改名称的学科ID: " << std::flush; 
						SET_TEXT_NORMAL(); 
						std::cin.clear(); 
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入新的学科名称: " << std::flush; 
					std::getline(std::cin, name); 
					info.GetSubjectList().at(id)->SetName(name); 
					break; 
				}
				case 'C': case 'c': 
				{
					basic_info::idType id; 
					basic_info::scoreType fullScore; 
					std::cout << "请依次输入要修改名称的学科ID和满分: " << std::endl;
					while (!(std::cin >> id >> fullScore) || info.GetSubjectList().find(id) == info.GetSubjectList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "没有该ID的课程，请重新输入要修改名称的学科ID和满分: " << std::flush; 
						else std::cout << "输入非法，请重新输入要修改名称的学科ID和满分: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					}
					info.GetSubjectList().at(id)->SetFullScore(fullScore); 
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					break; 
				}
				case 'D': case 'd':
				{
					basic_info::idType id;
					int credit;
					std::cout << "请依次输入要修改名称的学科ID和学分: " << std::endl;
					while (!(std::cin >> id >> credit) || info.GetSubjectList().find(id) == info.GetSubjectList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "没有该ID的学科，请重新输入要修改名称的学科ID和满学分: " << std::flush;
						else std::cout << "输入非法，请重新输入要修改名称的学科ID和学分: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					info.GetSubjectList().at(id)->SetCredit(credit);
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				default: 
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
				case 'E': case 'e':
					break; 
				}
				break; 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			case 'C': case 'c':
				std::cout << "请选择：A.更改班级ID\tB.更改班级名称\tC.取消" << std::endl;
				buf = 0; 
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
				{
					basic_info::idType srcID, newID;
					std::cout << "请依次输入班级原ID和新ID: " << std::endl;
					while (!(std::cin >> srcID >> newID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "输入非法，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeClassID(srcID, newID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_class:
						SET_TEXT_WARNING();
						std::cout << "该班级不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::class_exist:
						SET_TEXT_WARNING();
						std::cout << "新ID已被占用，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				case 'B': case 'b':
				{
					basic_info::idType id;
					std::string name;
					std::cout << "请输入要修改名称的班级ID: " << std::flush;
					while (!(std::cin >> id) || info.GetClassList().find(id) == info.GetClassList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "该班级不存在，请重新输入要修改名称的班级ID: " << std::flush;
						else std::cout << "输入非法，请重新输入要修改名称的班级ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入新的班级名称: " << std::flush;
					std::getline(std::cin, name);
					info.GetClassList().at(id)->SetName(name);
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
				case 'C': case 'c': 
					break;
				}
				break; 
			case 'D': case 'd': 
				std::cout << "请选择：A.更改学生ID\tB.更改学生姓名\tC.更改学生性别\tD.更改学生班级\tE.更改学生分数\tF.取消" << std::endl;
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				switch (buf)
				{
				case 'A': case 'a': 
				{
					basic_info::idType srcID, newID;
					std::cout << "请依次输入学生原ID和新ID: " << std::endl;
					while (!(std::cin >> srcID >> newID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "输入非法，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeStudentID(srcID, newID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_student:
						SET_TEXT_WARNING();
						std::cout << "该学生不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::student_exist:
						SET_TEXT_WARNING();
						std::cout << "新ID已被占用，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break; 
				}
				case 'B': case 'b': 
				{
					basic_info::idType id; 
					std::string name; 
					std::cout << "请输入您要更改姓名的学生ID: " << std::flush; 
					while (!(std::cin >> id) || info.GetStudentList().find(id) == info.GetStudentList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "该学生不存在！请重新输入您要更改姓名的学生ID: " << std::endl; 
						else std::cout << "输入非法！请重新输入您要更改姓名的学生ID: " << std::endl; 
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cout << "请输入学生的新姓名: " << std::flush;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					std::getline(std::cin, name); 
					info.GetStudentList().at(id)->SetName(name); 
					SET_TEXT_SUCCESS(); 
					std::cout << "更改学生姓名成功！" << std::endl; 
					SET_TEXT_NORMAL();
					break; 
				}
				case 'C': case 'c': 
				{
					basic_info::idType id; 
					std::cout << "请输入要更改性别的学生ID: " << std::flush; 
					while (!(std::cin >> id) || info.GetStudentList().find(id) == info.GetStudentList().end())
					{
						SET_TEXT_WARNING(); 
						if (std::cin) std::cout << "输入非法，请重新输入要更改性别的学生ID: " << std::flush;
						else std::cout << "该学生不存在！请重新输入要更改性别的学生ID: " << std::flush; 
						SET_TEXT_NORMAL(); 
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "当前学生名字: " << info.GetStudentList().at(id)->GetName() << ", 学生性别: " 
						<< (info.GetStudentList().at(id)->GetGender() == Student::genderType::male ? "男" : "女") << std::endl; 
					std::cout << "你确定要更改学生性别吗? (Y/n): " << std::flush; 
					buf = 0; 
					while(true)
					{
						std::cin >> buf; 
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
						switch (buf)
						{
						case 'Y': case 'y': 
							info.GetStudentList().at(id)->ReverseGender(); 
							SET_TEXT_SUCCESS();
							std::cout << "修改性别成功！" << std::endl;
							SET_TEXT_NORMAL();
							break; 
						case 'N': case 'n': 
							SET_TEXT_SUCCESS();
							std::cout << "您取消了性别修改" << std::endl;
							SET_TEXT_NORMAL();
							break; 
						default: 
							SET_TEXT_WARNING();
							std::cout << "输入非法！你确定要更改学生性别吗? (Y/n): " << std::flush; 
							SET_TEXT_NORMAL();
							continue; 
						}
						break; 
					}
					break; 
				}
				case 'D': case 'd': 
				{
					basic_info::idType studentID, classID; 
					std::cout << "请依次输入学生ID和新班级的ID: " << std::endl; 
					while (!(std::cin >> studentID >> classID))
					{
						SET_TEXT_WARNING(); 
						std::cout << "输入非法！请重新输入学生ID和新班级的ID: " << std::endl; 
						SET_TEXT_NORMAL(); 
						std::cin.clear(); 
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					switch (ChangeInfo::ChangeStudentClass(studentID, classID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_student: 
						SET_TEXT_WARNING();
						std::cout << "修改失败！该学生不存在！" << std::endl;
						SET_TEXT_NORMAL(); 
						break; 
					case ChangeInfo::operr::no_class:
						SET_TEXT_WARNING();
						std::cout << "修改失败！新班级不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break; 
				}
				case 'E': case 'e':
				{
					basic_info::idType studentID, subjectID;
					basic_info::scoreType newScore; 
					std::cout << "请依次输入学生ID、要更改的学科ID以及新的分数: " << std::endl;
					while (!(std::cin >> studentID >> subjectID >> newScore))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入学生ID、要更改的学科ID以及新的分数: " << std::endl;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					switch (ChangeInfo::ChangeStudentScore(studentID, subjectID, newScore))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_student:
						SET_TEXT_WARNING();
						std::cout << "修改失败！该学生不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_subject:
						SET_TEXT_WARNING();
						std::cout << "修改失败！该学生没有这门学科的成绩！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				default: 
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
				case 'F': case 'f':
					break;
				}
				break; 
			default: 
				SET_TEXT_WARNING(); 
				std::cout << "输入非法！" << std::endl; 
				SET_TEXT_NORMAL(); 
			}
			break; 
		}
		case 'I': case 'i': 
		{
			std::cout << "请选择: A.返回上一级\tB.根据ID查找\tC.根据姓名查找" << std::endl; 
			buf = 0; 
			while (true)
			{
				std::cin >> buf; 
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				switch (buf)
				{
				case 'A': case 'a':
					break;
				case 'B': case 'b': 
				{
					basic_info::idType studentID; 
					std::cout << "请输入您要查找的学生ID: " << std::flush; 
					while (!(std::cin >> studentID))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请输入您要查找的学生ID: " << std::flush; 
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().find(studentID); 
					if (itr == info.GetStudentList().end())
					{
						SET_TEXT_WARNING();
						std::cout << "您要找的学生不存在" << std::endl;
						SET_TEXT_NORMAL();
					}
					else
					{
						PrintStudentInfoHead(false); 
						PrintStudentInfo(info.GetStudentList().at(studentID), 0); 
					}
					break; 
				}
				case 'C': case 'c': 
				{
					std::string name; 
					bool exist = false; 
					std::cout << "请输入您要查找的学生姓名: " << std::flush; 
					std::getline(std::cin, name); 
					for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
						itr != info.GetStudentList().end(); ++itr)
					{
						if (itr->second->GetName() == name)
						{
							if (!exist)
							{
								PrintStudentInfoHead(false); 
								exist = true; 
							}
							PrintStudentInfo(itr->second, 0); 
						}
					}
					if (!exist)
					{
						SET_TEXT_WARNING();
						std::cout << "您要找的学生不存在" << std::endl;
						SET_TEXT_NORMAL(); 
					}
					break; 
				}
				default: 
					SET_TEXT_WARNING();
					std::cout << "输入非法！请选择: A.返回上一级\tB.根据ID查找\tC.根据姓名查找" << std::endl; 
					SET_TEXT_NORMAL();
					continue; 
				}
				break; 
			}
			break; 
		}
		case 'J': case 'j':
		{
			std::cout << "请选择: A.删除学科\tB.删除班级\tC.删除学生\tD.删除学生学习的某学科成绩\tE.返回上一级" << std::endl; 
			buf = 0; 
			while (true)
			{
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
					break;
				case 'B': case 'b': 
				{
					delSubject: 
					basic_info::idType id; 
					std::cout << "请输入您要删除的学科ID: " << std::flush; 
					while (!(std::cin >> id))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入您要删除的学科ID: " << std::flush;
						SET_TEXT_NORMAL(); 
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					SET_TEXT_WARNING(); 
					std::cout << "这样做会永久删除与该学科相关的所有信息，包括学生的成绩，您确定要这样做吗?(Y/n): " << std::flush; 
					SET_TEXT_NORMAL(); 
					buf = 0; 
					while (true)
					{
						std::cin >> buf; 
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
						switch (buf)
						{
						case 'Y': case 'y': 
							if (ChangeInfo::DeleteSubject(id))
							{
								SET_TEXT_SUCCESS(); std::cout << "成功删除学科: " << id << std::endl; SET_TEXT_NORMAL();
							}
							else
							{
								SET_TEXT_WARNING(); std::cout << "删除失败！该学科不存在！" << std::endl; SET_TEXT_NORMAL();
							}
							break; 
						case 'N': case 'n': 
							SET_TEXT_SUCCESS();
							std::cout << "已取消删除操作！" << std::endl;
							SET_TEXT_NORMAL();
							break; 
						default: 
							SET_TEXT_WARNING();
							std::cout << "输入非法！\n删除该学科会删除与该学科相关的所有信息，包括学生的成绩，您确定要这样做吗?(Y/n): " << std::flush;
							SET_TEXT_NORMAL(); 
							continue; 
						}
						break; 
					}
					std::cout << "是否继续删除学科?(Y/n)" << std::endl; 
					buf = 0; 
					std::cin >> buf; 
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					if (buf == 'Y' || buf == 'y') goto delSubject; 
					break; 
				}
				case 'C': case 'c': 
				{
				delClass:
					basic_info::idType id;
					std::cout << "请输入您要删除的班级ID: " << std::flush;
					while (!(std::cin >> id))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入您要删除的班级ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					SET_TEXT_WARNING();
					std::cout << "该操作不可恢复，您确定要删除该班级吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL();
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'Y': case 'y':
							switch (ChangeInfo::DeleteClass(id))
							{
							case ChangeInfo::operr::success: 
								SET_TEXT_SUCCESS();
								std::cout << "成功删除班级: " << id << std::endl;
								SET_TEXT_NORMAL();
								break; 
							case ChangeInfo::operr::no_class: 
								SET_TEXT_WARNING();
								std::cout << "删除失败！该班级不存在！" << std::endl;
								SET_TEXT_NORMAL();
								break; 
							case ChangeInfo::operr::student_exist: 
								SET_TEXT_WARNING();
								std::cout << "删除失败！该班级仍有学生，删除前请先将班级清空！" << std::endl;
								SET_TEXT_NORMAL();
								break; 
							}
							break;
						case 'N': case 'n':
							SET_TEXT_SUCCESS();
							std::cout << "已取消删除操作！" << std::endl;
							SET_TEXT_NORMAL();
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！\n删除该班级不可恢复，您确定要删除该班级吗?(Y/n): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					}
					std::cout << "是否继续删除班级?(Y/n)" << std::endl;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto delClass;
					break; 
				}
				case 'D': case 'd': 
				{
				delStudent:
					basic_info::idType id;
					std::cout << "请输入您要删除的学生ID: " << std::flush;
					while (!(std::cin >> id))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入您要删除的学生ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					SET_TEXT_WARNING();
					std::cout << "这样做会永久删除该学生的所有信息，您确定要这样做吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL();
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'Y': case 'y':
							if (ChangeInfo::DeleteStudent(id))
							{
								SET_TEXT_SUCCESS(); std::cout << "成功删除学生: " << id << std::endl; SET_TEXT_NORMAL();
							}
							else
							{
								SET_TEXT_WARNING(); std::cout << "删除失败！该学生不存在！" << std::endl; SET_TEXT_NORMAL();
							}
							break;
						case 'N': case 'n':
							SET_TEXT_SUCCESS();
							std::cout << "已取消删除操作！" << std::endl;
							SET_TEXT_NORMAL();
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！\n删除该学生会永久删除该学生的所有信息，您确定要这样做吗?(Y/n): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					}
					std::cout << "是否继续删除学生?(Y/n)" << std::endl;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto delStudent;
					break; 
				}
				case 'E': case 'e':
				{
					{
					delStudentSubject:
						basic_info::idType studentID, subjectID;
						std::cout << "请依次输入您要删除成绩的学生ID和学科ID: " << std::endl;
						while (!(std::cin >> studentID >> subjectID))
						{
							SET_TEXT_WARNING();
							std::cout << "输入非法！请重新输入您要删除的班级ID: " << std::flush;
							SET_TEXT_NORMAL();
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "该操作不可恢复，您确定要删除该学生的该科成绩吗?(Y/n): " << std::flush;
						SET_TEXT_NORMAL();
						buf = 0;
						while (true)
						{
							std::cin >> buf;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							switch (buf)
							{
							case 'Y': case 'y':
								switch (ChangeInfo::DeleteStudentSubject(studentID, subjectID))
								{
								case ChangeInfo::operr::success:
									SET_TEXT_SUCCESS();
									std::cout << "成功删除学生: " << studentID << "的学科: " << subjectID << "的成绩" << std::endl;
									SET_TEXT_NORMAL();
									break;
								case ChangeInfo::operr::no_student:
									SET_TEXT_WARNING();
									std::cout << "删除失败！该学生不存在！" << std::endl;
									SET_TEXT_NORMAL();
									break;
								case ChangeInfo::operr::no_subject:
									SET_TEXT_WARNING();
									std::cout << "删除失败！该学生无该学科的成绩！" << std::endl;
									SET_TEXT_NORMAL();
									break;
								}
								break;
							case 'N': case 'n':
								SET_TEXT_SUCCESS();
								std::cout << "已取消删除操作！" << std::endl;
								SET_TEXT_NORMAL();
								break;
							default:
								SET_TEXT_WARNING();
								std::cout << "输入非法！\n删除学生成绩不可恢复，您确定要删除该学生的该科成绩吗?(Y/n): " << std::flush;
								SET_TEXT_NORMAL();
								continue;
							}
							break;
						}
						std::cout << "是否继续删除班级?(Y/n)" << std::endl;
						buf = 0;
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (buf == 'Y' || buf == 'y') goto delStudentSubject;
						break;
					}
					break; 
				}
				default: 
					SET_TEXT_WARNING();
					std::cout << "输入非法！请选择: A.删除学科\tB.删除班级\tC.删除学生\tD.删除学生学习的某学科成绩\tE.返回上一级" << std::endl;
					SET_TEXT_NORMAL(); 
					continue; 
				}
				break; 
			}
			break; 
		}
		case 'K': case 'k': 
		{
			std::string fileName; 
			std::cout << "请输入要读取的文件名称" << std::endl; 
			std::getline(std::cin, fileName); 
			bool hasReadStudent = false;			//记录是否录入了学生
			std::list<basic_info*> readInfo; 
			std::cout << "开始读入数据，请等待..." << std::endl; 
			readInfo = ChangeInfo::ReadFromFile(fileName); 
			size_t subNum = 0, clsNum = 0, stuNum = 0, stuSubNum = 0, errNum = 0; 
			for (std::list<basic_info*>::const_iterator itr = readInfo.begin();
				itr != readInfo.end(); ++itr)
			{
				if (!(*itr))						//读入错误
				{
					++errNum;
					SET_TEXT_WARNING(); 
					std::cout << "该对象读入错误" << std::endl; 
					SET_TEXT_NORMAL(); 
					continue; 
				}
				else if (*itr == (basic_info*)(-1))	//开始读入学生
				{
					hasReadStudent = true; 
					continue; 
				}
				switch ((*itr)->GetObjType())
				{
				case basic_info::objtype::bSubject: 
					SET_TEXT_SUCCESS(); 
					if (hasReadStudent)
					{
						++stuSubNum; 
						std::cout << "成功为学生录入课程: " << (*itr)->GetID() << "的成绩" << std::endl; 
					}
					else
					{
						++subNum; 
						std::cout << "成功录入课程: " << (*itr)->GetID() << std::endl; 
					}
					SET_TEXT_NORMAL();
					break; 
				case basic_info::objtype::bClass:
					++clsNum; 
					SET_TEXT_SUCCESS(); 
					std::cout << "成功录入班级: " << (*itr)->GetID() << std::endl; 
					SET_TEXT_NORMAL(); 
					break; 
				case basic_info::objtype::bStudent: 
					(*itr)->GetID(); 
					++stuNum; 
					SET_TEXT_SUCCESS();
					std::cout << "成功录入学生: " << (*itr)->GetID() << std::endl;
					SET_TEXT_NORMAL(); 
					break; 
				}
			}
			SET_TEXT_SUCCESS(); 
			std::cout << "成功录入: 学科" << subNum << "个, 班级" << clsNum << "个, 学生" << stuNum << "个, 学生修习课程" << stuSubNum << "个" << std::endl; 
			std::cout << "共" << subNum + clsNum + stuNum + stuSubNum << "个" << std::endl; 
			SET_TEXT_WARNING(); 
			std::cout << "失败" << errNum << "个" << std::endl; 
			SET_TEXT_NORMAL(); 
			break; 
		}
		case 'L': case 'l': 
		{
			std::string fileName; 
			std::cout << "请输入您要保存的文件名称: " << std::flush; 
			std::getline(std::cin, fileName); 
			if (!ChangeInfo::SaveToFile(fileName))
			{
				SET_TEXT_WARNING(); std::cout << "存入文件失败！无法打开文件: " << fileName << std::endl; SET_TEXT_NORMAL(); 
			}
			else
			{
				SET_TEXT_SUCCESS(); std::cout << "成功存入文件" << fileName << std::endl; SET_TEXT_NORMAL();
			}
			break; 
		}
		case 'M': case 'm': 
			SET_TEXT_WARNING(); 
			std::cout << "清空所有数据将无法恢复，您确定要这样做吗?(Y/n): " << std::flush; 
			SET_TEXT_NORMAL();
			buf = 0; 
			while (true)
			{
				std::cin >> buf; 
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				switch (buf)
				{
				case 'Y': case 'y':
					ChangeInfo::Clear(); 
					SET_TEXT_SUCCESS(); std::cout << "已清空所有数据！" << std::flush; SET_TEXT_NORMAL();
					break; 
				case 'N': case 'n': 
					SET_TEXT_SUCCESS(); std::cout << "已成功取消清空操作！" << std::flush; SET_TEXT_NORMAL(); 
					break; 
				default: 
					SET_TEXT_WARNING();
					std::cout << "输入非法！清空所有数据将无法恢复，您确定要这样做吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL(); 
					continue; 
				}
				break; 
			}
			break; 
		default: 
			std::cout << "无此选项！" << std::endl; 
		}
	}
}

void UI::CompulsorySystem()

{
	system("cls");
	while (true)
	{
		std::cout << "当前：学生成绩管理系统学分模式" << std::endl;
		std::cout << "A.返回上一级\nB.显示当前的所有学科\nC.输出所有学生成绩\nD.输出某学科学生成绩\nE.输出某班级学生成绩\nF.输出所有班级\nG.添加\nH.更改\nI.查找学生成绩\nJ.删除\nK.读取存档（添加至当前成绩库）\nL.保存...\nM.清空所有数据" << std::endl;
		char buf = 0;
		std::cin >> buf;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (buf)
		{
		case 'A': case'a':
			SET_TEXT_WARNING();
			std::cout << "返回上一级会使数据全部丢失，请务必确认您的数据已经保存，您确定要继续吗? (Y/n): " << std::flush;
			buf = 0;
			while (true)
			{
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'Y': case 'y': case 'N': case 'n':
					break;
				default:
					std::cout << "输入非法! 返回上一级会使得数据全部丢失，你确定吗? (Y/n): " << std::flush;
					continue;
				}
				break;
			}
			SET_TEXT_NORMAL();
			if (buf == 'Y' || buf == 'y')
			{
				ChangeInfo::Clear();
				return;
			}
			break;
		case 'B': case 'b':
			PrintSubject();
			break;
		case 'C': case'c':
			std::cout << "是否按成绩排名?(Y/n)" << std::flush;
			while (true)
			{
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (buf == 'Y' || buf == 'y') { PrintStudent(true); break; }
				else if (buf == 'N' || buf == 'n') { PrintStudent(false); break; }
				else
				{
					SET_TEXT_WARNING(); std::cout << "输入非法！是否按成绩排名?(Y/n)" << std::flush; SET_TEXT_NORMAL();
				}
			}
			break;
		case 'D': case 'd':
		{
			basic_info::idType subjectID;
			std::cout << "请输入该学科的ID: " << std::flush;
			while (!(std::cin >> subjectID))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				SET_TEXT_WARNING();
				std::cout << "输入非法，请重新输入该学科的ID: " << std::flush;
				SET_TEXT_NORMAL();
			}
			std::cout << "是否按成绩排名?(Y/n)" << std::flush;
			while (true)
			{
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (buf == 'Y' || buf == 'y') { PrintSubjectStudent(subjectID, true); break; }
				else if (buf == 'N' || buf == 'n') { PrintSubjectStudent(subjectID, false); break; }
				else
				{
					SET_TEXT_WARNING(); std::cout << "输入非法！是否按成绩排名?(Y/n)" << std::flush; SET_TEXT_NORMAL();
				}
			}
			break;
		}
		case 'E': case 'e':
		{
			basic_info::idType classID;
			std::cout << "请输入该班级的ID: " << std::flush;
			while (!(std::cin >> classID))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				SET_TEXT_WARNING();
				std::cout << "输入非法，请重新输入！" << std::endl;
				SET_TEXT_NORMAL();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "是否按成绩排名?(Y/n)" << std::flush;
			while (true)
			{
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (buf == 'Y' || buf == 'y') { PrintClassStudent(classID, true); break; }
				else if (buf == 'N' || buf == 'n') { PrintClassStudent(classID, false); break; }
				else
				{
					SET_TEXT_WARNING(); std::cout << "输入非法！是否按成绩排名?(Y/n)" << std::flush; SET_TEXT_NORMAL();
				}
			}
			break;
		}
		case 'F': case 'f': 
		{
			PrintClass();
			break;
		}
		case 'G': case 'g':
		{
			std::cout << "请选择: A.返回上一级\tB.添加新学科\tC.添加新班级\tD.添加新学生" << std::endl;
			while (true)
			{
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
					break;
				case 'B': case 'b':
				{
				addNewSubject:
					basic_info::idType id;
					basic_info::scoreType fullScore;
					std::string name;
					std::cout << "请输入添加的新学科的ID: " << std::flush;
					while (!(std::cin >> id) || info.GetSubjectList().find(id) != info.GetSubjectList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "此班级ID已经被占用！请输入添加的新学科的ID: " << std::flush;
						else std::cout << "输入非法！请输入添加的新学科的ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入添加的新学科的名字: " << std::flush;
					std::getline(std::cin, name);
					std::cout << "请分别输入添加的新学科的满分数: " << std::endl;
					while (!(std::cin >> fullScore))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "输入非法！请分别输入添加的新学科的满分数: " << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (ChangeInfo::InsertSubject(id, name, fullScore, 1))
					{
						SET_TEXT_SUCCESS();
						std::cout << "添加新学科成功！" << std::endl;
						SET_TEXT_NORMAL(); 
						if (!info.GetStudentList().empty())				//学生不为空
						{
							std::cout << "是否为当前所有学生添加成绩(若不添加，则当前所有学生的成绩默认为零)?(Y/n): " << std::flush;
							buf = 0;
							while (true)
							{
								std::cin >> buf;
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								switch (buf)
								{
								case 'Y': case 'y':					//录入成绩
								{
									basic_info::scoreType score; 
									for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
										itr != info.GetStudentList().end(); ++itr)
									{
										std::cout << "请输入学生: " << itr->first << ' ' << itr->second->GetName() << " 的成绩: " << std::flush; 
										while (!(std::cin >> score))
										{
											SET_TEXT_WARNING(); 
											std::cout << "输入非法！请重新输入学生: " << itr->first << ' ' << itr->second->GetName() << " 的成绩: " << std::flush; 
											SET_TEXT_NORMAL();
											std::cin.clear();
											std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
										}
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
										ChangeInfo::AddStudentSubject(itr->first, id, score); 
										SET_TEXT_SUCCESS(); 
										std::cout << "成功将学生: " << itr->first << ' ' << itr->second->GetName() << " 的成绩置为: " << std::setprecision(2) << score << std::endl; 
										SET_TEXT_NORMAL();
									}
									break;
								}
								case 'N': case 'n':
								{
									for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
										itr != info.GetStudentList().end(); ++itr)
										ChangeInfo::AddStudentSubject(itr->first, id, 0);
									SET_TEXT_SUCCESS(); std::cout << "已把所有学生成绩置零" << std::endl; SET_TEXT_NORMAL();
									break;
								}
								default:
									SET_TEXT_WARNING();
									std::cout << "输入非法！\n是否为当前所有学生添加成绩(若不添加，则当前所有学生的成绩默认为零)?(Y/n): " << std::flush;
									SET_TEXT_NORMAL();
									continue;
								}
								break;
							}
						}
					}
					else
					{
						SET_TEXT_WARNING();
						std::cout << "添加失败！未知错误！" << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cout << "是否继续添加学科?(Y/n): " << std::flush;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					if (buf == 'Y' || buf == 'y') goto addNewSubject;
					break;
				}
				case 'C': case'c':
				{
				addNewClass:
					basic_info::idType id;
					std::string name;
					std::cout << "请输入添加的新班级的ID: " << std::flush;
					while (!(std::cin >> id) || info.GetClassList().find(id) != info.GetClassList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin)
							std::cout << "此班级ID已经被占用！请输入添加的新班级的ID: " << std::flush;
						else std::cout << "输入非法！请输入添加的新班级的ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入添加的新班级的名字: " << std::flush;
					std::getline(std::cin, name);
					if (ChangeInfo::InsertClass(id, name))
					{
						SET_TEXT_SUCCESS(); std::cout << "添加新班级成功！" << std::endl; SET_TEXT_NORMAL();
					}
					else
					{
						SET_TEXT_WARNING(); std::cout << "添加失败！未知错误！" << std::endl; SET_TEXT_NORMAL();
					}
					std::cout << "是否继续添加?(Y/n): " << std::flush;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto addNewClass;
					break;
				}
				case 'D': case'd':
				{
				addNewStudent:
					basic_info::idType id, classID;
					std::string name;
					Student::genderType gender = Student::genderType::male;
					std::cout << "请输入添加的新学生的ID: " << std::flush;
					while (!(std::cin >> id) || info.GetStudentList().find(id) != info.GetStudentList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin)
							std::cout << "此学生ID已经被占用！请输入添加的新班级的ID: " << std::flush;
						else std::cout << "输入非法！请输入添加的新学生的ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入添加的新学生的名字: " << std::flush;
					std::getline(std::cin, name);
					std::cout << "请输入学生的性别(m/f: m-male, f-female): " << std::flush;
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'M': case'm':
							gender = Student::genderType::male;
							break;
						case 'F': case'f':
							gender = Student::genderType::female;
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！请输入学生的性别(m/f: m-male, f-female): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					};
					std::cout << "请输入该学生所属班级的ID: " << std::flush;
					while (!(std::cin >> classID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
						SET_TEXT_WARNING();
						std::cout << "输入非法！请输入该学生所属班级的ID: " << std::flush;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					if (ChangeInfo::InsertStudent(id, name, gender, classID))
					{
						SET_TEXT_SUCCESS(); std::cout << "添加新学生成功！" << std::endl; SET_TEXT_NORMAL(); 
						std::cout << "是否为该学生录入各科成绩(若不录入，则默认各科成绩为零)?(Y/n): " << std::flush; 
						buf = 0; 
						while (true)
						{
							std::cin >> buf; 
							std::cin.clear(); 
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
							switch (buf)
							{
							case 'Y': case 'y': 
							{
								basic_info::scoreType score; 
								for (std::map<basic_info::idType, Subject*>::const_iterator itr = info.GetSubjectList().begin();
									itr != info.GetSubjectList().end(); ++itr)
								{
									std::cout << "请输入该同学在学科: " << itr->first << ' ' << itr->second->GetName() << " 上所取得的成绩: " << std::flush; 
									while (!(std::cin >> score))
									{
										SET_TEXT_WARNING();
										std::cout << "输入非法！请重新输入该同学在学科: " << itr->first << ' ' << itr->second->GetName() << " 上所取得的成绩: " << std::flush; 
										SET_TEXT_NORMAL();
										std::cin.clear();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
									ChangeInfo::AddStudentSubject(id, itr->first, score); 
									SET_TEXT_SUCCESS(); std::cout << "成功录入该学科成绩！" << std::endl; SET_TEXT_NORMAL(); 
								}
								break; 
							}
							case 'N': case 'n': 
							{
								for (std::map<basic_info::idType, Subject*>::const_iterator itr = info.GetSubjectList().begin();
									itr != info.GetSubjectList().end(); ++itr)
									ChangeInfo::AddStudentSubject(id, itr->first, 0); 
								SET_TEXT_SUCCESS(); std::cout << "已将该同学的所有成绩置为零！" << std::endl; SET_TEXT_NORMAL();
								break; 
							}
							default: 
								SET_TEXT_WARNING(); 
								std::cout << "输入非法！是否为该学生录入各科成绩(若不录入，则默认各科成绩为零)?(Y/n): " << std::flush; 
								SET_TEXT_NORMAL();
								continue; 
							}
							break; 
						}
					}
					else
					{
						SET_TEXT_WARNING(); std::cout << "添加失败！不存在此班级！" << std::endl; SET_TEXT_NORMAL();
					}
					std::cout << "是否继续添加?(Y/n): " << std::flush;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto addNewStudent;
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
					continue;
				}
				break;
			}
			break;
		}
		case 'H': case 'h':
		{
			std::cout << "请选择: A.返回上一级\tB.更改学科信息\tC.更改班级信息\tD.更改学生信息" << std::endl;
			buf = 0;
			std::cin >> buf;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (buf)
			{
			case 'A': case 'a':
				break;
			case 'B': case 'b':
				std::cout << "请选择：A.更改学科ID\tB.更改学科名称\tC.修改学科满分\tD.取消" << std::endl;
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
				{
					basic_info::idType srcID, newID;
					std::cout << "请依次输入学科原ID和新ID: " << std::endl;
					while (!(std::cin >> srcID >> newID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "输入非法，请重新输入学科原ID和新ID: " << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeSubjectID(srcID, newID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_subject:
						SET_TEXT_WARNING();
						std::cout << "该学科不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::subject_exist:
						SET_TEXT_WARNING();
						std::cout << "新ID已被占用，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				case 'B': case 'b':
				{
					basic_info::idType id;
					std::string name;
					std::cout << "请输入要修改名称的学科ID: " << std::flush;
					while (!(std::cin >> id) || info.GetSubjectList().find(id) == info.GetSubjectList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "该学科不存在，请重新输入要修改名称的学科ID: " << std::flush;
						else std::cout << "输入非法，请重新输入要修改名称的学科ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入新的学科名称: " << std::flush;
					std::getline(std::cin, name);
					info.GetSubjectList().at(id)->SetName(name);
					break;
				}
				case 'C': case 'c':
				{
					basic_info::idType id;
					basic_info::scoreType fullScore;
					std::cout << "请依次输入要修改名称的学科ID和满分: " << std::endl;
					while (!(std::cin >> id >> fullScore) || info.GetSubjectList().find(id) == info.GetSubjectList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "没有该ID的课程，请重新输入要修改名称的学科ID和满分: " << std::flush;
						else std::cout << "输入非法，请重新输入要修改名称的学科ID和满分: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					info.GetSubjectList().at(id)->SetFullScore(fullScore);
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
				case 'D': case 'd':
					break;
				}
				break;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			case 'C': case 'c':
				std::cout << "请选择：A.更改班级ID\tB.更改班级名称\tC.取消" << std::endl;
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
				{
					basic_info::idType srcID, newID;
					std::cout << "请依次输入班级原ID和新ID: " << std::endl;
					while (!(std::cin >> srcID >> newID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "输入非法，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeClassID(srcID, newID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_class:
						SET_TEXT_WARNING();
						std::cout << "该班级不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::class_exist:
						SET_TEXT_WARNING();
						std::cout << "新ID已被占用，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				case 'B': case 'b':
				{
					basic_info::idType id;
					std::string name;
					std::cout << "请输入要修改名称的班级ID: " << std::flush;
					while (!(std::cin >> id) || info.GetClassList().find(id) == info.GetClassList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "该班级不存在，请重新输入要修改名称的班级ID: " << std::flush;
						else std::cout << "输入非法，请重新输入要修改名称的班级ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "请输入新的班级名称: " << std::flush;
					std::getline(std::cin, name);
					info.GetClassList().at(id)->SetName(name);
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
				case 'C': case 'c':
					break;
				}
				break;
			case 'D': case 'd':
				std::cout << "请选择：A.更改学生ID\tB.更改学生姓名\tC.更改学生性别\tD.更改学生班级\tE.更改学生分数\tF.取消" << std::endl;
				buf = 0;
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
				{
					basic_info::idType srcID, newID;
					std::cout << "请依次输入学生原ID和新ID: " << std::endl;
					while (!(std::cin >> srcID >> newID))
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						SET_TEXT_WARNING();
						std::cout << "输入非法，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeStudentID(srcID, newID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_student:
						SET_TEXT_WARNING();
						std::cout << "该学生不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::student_exist:
						SET_TEXT_WARNING();
						std::cout << "新ID已被占用，修改失败！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				case 'B': case 'b':
				{
					basic_info::idType id;
					std::string name;
					std::cout << "请输入您要更改姓名的学生ID: " << std::flush;
					while (!(std::cin >> id) || info.GetStudentList().find(id) == info.GetStudentList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "该学生不存在！请重新输入您要更改姓名的学生ID: " << std::endl;
						else std::cout << "输入非法！请重新输入您要更改姓名的学生ID: " << std::endl;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cout << "请输入学生的新姓名: " << std::flush;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::getline(std::cin, name);
					info.GetStudentList().at(id)->SetName(name);
					SET_TEXT_SUCCESS();
					std::cout << "更改学生姓名成功！" << std::endl;
					SET_TEXT_NORMAL();
					break;
				}
				case 'C': case 'c':
				{
					basic_info::idType id;
					std::cout << "请输入要更改性别的学生ID: " << std::flush;
					while (!(std::cin >> id) || info.GetStudentList().find(id) == info.GetStudentList().end())
					{
						SET_TEXT_WARNING();
						if (std::cin) std::cout << "输入非法，请重新输入要更改性别的学生ID: " << std::flush;
						else std::cout << "该学生不存在！请重新输入要更改性别的学生ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "当前学生名字: " << info.GetStudentList().at(id)->GetName() << ", 学生性别: "
						<< (info.GetStudentList().at(id)->GetGender() == Student::genderType::male ? "男" : "女") << std::endl;
					std::cout << "你确定要更改学生性别吗? (Y/n): " << std::flush;
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'Y': case 'y':
							info.GetStudentList().at(id)->ReverseGender();
							SET_TEXT_SUCCESS();
							std::cout << "修改性别成功！" << std::endl;
							SET_TEXT_NORMAL();
							break;
						case 'N': case 'n':
							SET_TEXT_SUCCESS();
							std::cout << "您取消了性别修改" << std::endl;
							SET_TEXT_NORMAL();
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！你确定要更改学生性别吗? (Y/n): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					}
					break;
				}
				case 'D': case 'd':
				{
					basic_info::idType studentID, classID;
					std::cout << "请依次输入学生ID和新班级的ID: " << std::endl;
					while (!(std::cin >> studentID >> classID))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入学生ID和新班级的ID: " << std::endl;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeStudentClass(studentID, classID))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_student:
						SET_TEXT_WARNING();
						std::cout << "修改失败！该学生不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_class:
						SET_TEXT_WARNING();
						std::cout << "修改失败！新班级不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				case 'E': case 'e':
				{
					basic_info::idType studentID, subjectID;
					basic_info::scoreType newScore;
					std::cout << "请依次输入学生ID、要更改的学科ID以及新的分数: " << std::endl;
					while (!(std::cin >> studentID >> subjectID >> newScore))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入学生ID、要更改的学科ID以及新的分数: " << std::endl;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					switch (ChangeInfo::ChangeStudentScore(studentID, subjectID, newScore))
					{
					case ChangeInfo::operr::success:
						SET_TEXT_SUCCESS();
						std::cout << "修改成功！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_student:
						SET_TEXT_WARNING();
						std::cout << "修改失败！该学生不存在！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					case ChangeInfo::operr::no_subject:
						SET_TEXT_WARNING();
						std::cout << "修改失败！该学生没有这门学科的成绩！" << std::endl;
						SET_TEXT_NORMAL();
						break;
					}
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！" << std::endl;
					SET_TEXT_NORMAL();
				case 'F': case 'f':
					break;
				}
				break;
			default:
				SET_TEXT_WARNING();
				std::cout << "输入非法！" << std::endl;
				SET_TEXT_NORMAL();
			}
			break;
		}
		case 'I': case 'i':
		{
			std::cout << "请选择: A.返回上一级\tB.根据ID查找\tC.根据姓名查找" << std::endl;
			buf = 0;
			while (true)
			{
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
					break;
				case 'B': case 'b':
				{
					basic_info::idType studentID;
					std::cout << "请输入您要查找的学生ID: " << std::flush;
					while (!(std::cin >> studentID))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请输入您要查找的学生ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().find(studentID);
					if (itr == info.GetStudentList().end())
					{
						SET_TEXT_WARNING();
						std::cout << "您要找的学生不存在" << std::endl;
						SET_TEXT_NORMAL();
					}
					else
					{
						PrintStudentInfoHead(false);
						PrintStudentInfo(info.GetStudentList().at(studentID), 0);
					}
					break;
				}
				case 'C': case 'c':
				{
					std::string name;
					bool exist = false;
					std::cout << "请输入您要查找的学生姓名: " << std::flush;
					std::getline(std::cin, name);
					for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
						itr != info.GetStudentList().end(); ++itr)
					{
						if (itr->second->GetName() == name)
						{
							if (!exist)
							{
								PrintStudentInfoHead(false);
								exist = true;
							}
							PrintStudentInfo(itr->second, 0);
						}
					}
					if (!exist)
					{
						SET_TEXT_WARNING();
						std::cout << "您要找的学生不存在" << std::endl;
						SET_TEXT_NORMAL();
					}
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！请选择: A.返回上一级\tB.根据ID查找\tC.根据姓名查找" << std::endl;
					SET_TEXT_NORMAL();
					continue;
				}
				break;
			}
			break;
		}
		case 'J': case 'j':
		{
			std::cout << "请选择: A.返回上一级\tB.删除学科\tC.删除班级\tD.删除学生" << std::endl;
			buf = 0;
			while (true)
			{
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'A': case 'a':
					break;
				case 'B': case 'b':
				{
				delSubject:
					basic_info::idType id;
					std::cout << "请输入您要删除的学科ID: " << std::flush;
					while (!(std::cin >> id))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入您要删除的学科ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					SET_TEXT_WARNING();
					std::cout << "这样做会永久删除与该学科相关的所有信息，包括学生的成绩，您确定要这样做吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL();
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'Y': case 'y':
							if (ChangeInfo::DeleteSubject(id))
							{
								SET_TEXT_SUCCESS(); std::cout << "成功删除学科: " << id << std::endl; SET_TEXT_NORMAL();
							}
							else
							{
								SET_TEXT_WARNING(); std::cout << "删除失败！该学科不存在！" << std::endl; SET_TEXT_NORMAL();
							}
							break;
						case 'N': case 'n':
							SET_TEXT_SUCCESS();
							std::cout << "已取消删除操作！" << std::endl;
							SET_TEXT_NORMAL();
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！\n删除该学科会删除与该学科相关的所有信息，包括学生的成绩，您确定要这样做吗?(Y/n): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					}
					std::cout << "是否继续删除学科?(Y/n)" << std::endl;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto delSubject;
					break;
				}
				case 'C': case 'c':
				{
				delClass:
					basic_info::idType id;
					std::cout << "请输入您要删除的班级ID: " << std::flush;
					while (!(std::cin >> id))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入您要删除的班级ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					SET_TEXT_WARNING();
					std::cout << "该操作不可恢复，您确定要删除该班级吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL();
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'Y': case 'y':
							switch (ChangeInfo::DeleteClass(id))
							{
							case ChangeInfo::operr::success:
								SET_TEXT_SUCCESS();
								std::cout << "成功删除班级: " << id << std::endl;
								SET_TEXT_NORMAL();
								break;
							case ChangeInfo::operr::no_class:
								SET_TEXT_WARNING();
								std::cout << "删除失败！该班级不存在！" << std::endl;
								SET_TEXT_NORMAL();
								break;
							case ChangeInfo::operr::student_exist:
								SET_TEXT_WARNING();
								std::cout << "删除失败！该班级仍有学生，删除前请先将班级清空！" << std::endl;
								SET_TEXT_NORMAL();
								break;
							}
							break;
						case 'N': case 'n':
							SET_TEXT_SUCCESS();
							std::cout << "已取消删除操作！" << std::endl;
							SET_TEXT_NORMAL();
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！\n删除该班级不可恢复，您确定要删除该班级吗?(Y/n): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					}
					std::cout << "是否继续删除班级?(Y/n)" << std::endl;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto delClass;
					break;
				}
				case 'D': case 'd':
				{
				delStudent:
					basic_info::idType id;
					std::cout << "请输入您要删除的学生ID: " << std::flush;
					while (!(std::cin >> id))
					{
						SET_TEXT_WARNING();
						std::cout << "输入非法！请重新输入您要删除的学生ID: " << std::flush;
						SET_TEXT_NORMAL();
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					SET_TEXT_WARNING();
					std::cout << "这样做会永久删除该学生的所有信息，您确定要这样做吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL();
					buf = 0;
					while (true)
					{
						std::cin >> buf;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						switch (buf)
						{
						case 'Y': case 'y':
							if (ChangeInfo::DeleteStudent(id))
							{
								SET_TEXT_SUCCESS(); std::cout << "成功删除学生: " << id << std::endl; SET_TEXT_NORMAL();
							}
							else
							{
								SET_TEXT_WARNING(); std::cout << "删除失败！该学生不存在！" << std::endl; SET_TEXT_NORMAL();
							}
							break;
						case 'N': case 'n':
							SET_TEXT_SUCCESS();
							std::cout << "已取消删除操作！" << std::endl;
							SET_TEXT_NORMAL();
							break;
						default:
							SET_TEXT_WARNING();
							std::cout << "输入非法！\n删除该学生会永久删除该学生的所有信息，您确定要这样做吗?(Y/n): " << std::flush;
							SET_TEXT_NORMAL();
							continue;
						}
						break;
					}
					std::cout << "是否继续删除学生?(Y/n)" << std::endl;
					buf = 0;
					std::cin >> buf;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (buf == 'Y' || buf == 'y') goto delStudent;
					break;
				}
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！请选择: A.返回上一级\tB.删除学科\tC.删除班级\tD.删除学生" << std::endl;
					SET_TEXT_NORMAL();
					continue;
				}
				break;
			}
			break;
		}
		case 'K': case 'k':
		{
			std::string fileName;
			std::cout << "请输入要读取的文件名称" << std::endl;
			std::getline(std::cin, fileName);
			bool hasReadStudent = false;			//记录是否录入了学生
			std::list<basic_info*> readInfo;
			std::cout << "开始读入数据，请等待..." << std::endl;
			readInfo = ChangeInfo::ReadFromFile(fileName);
			size_t subNum = 0, clsNum = 0, stuNum = 0, stuSubNum = 0, errNum = 0;
			for (std::list<basic_info*>::const_iterator itr = readInfo.begin();
				itr != readInfo.end(); ++itr)
			{
				if (!(*itr))						//读入错误
				{
					++errNum;
					SET_TEXT_WARNING();
					std::cout << "该对象读入错误" << std::endl;
					SET_TEXT_NORMAL();
					continue;
				}
				else if (*itr == (basic_info*)(-1))	//开始读入学生
				{
					hasReadStudent = true;
					continue;
				}
				switch ((*itr)->GetObjType())
				{
				case basic_info::objtype::bSubject:
					SET_TEXT_SUCCESS();
					if (hasReadStudent)
					{
						++stuSubNum;
						std::cout << "成功为学生录入课程: " << (*itr)->GetID() << "的成绩" << std::endl;
					}
					else
					{
						++subNum;
						std::cout << "成功录入课程: " << (*itr)->GetID() << std::endl;
					}
					SET_TEXT_NORMAL();
					break;
				case basic_info::objtype::bClass:
					++clsNum;
					SET_TEXT_SUCCESS();
					std::cout << "成功录入班级: " << (*itr)->GetID() << std::endl;
					SET_TEXT_NORMAL();
					break;
				case basic_info::objtype::bStudent:
					(*itr)->GetID();
					++stuNum;
					SET_TEXT_SUCCESS();
					std::cout << "成功录入学生: " << (*itr)->GetID() << std::endl;
					SET_TEXT_NORMAL();
					break;
				}
			}
			SET_TEXT_SUCCESS();
			std::cout << "成功录入: 学科" << subNum << "个, 班级" << clsNum << "个, 学生" << stuNum << "个, 学生修习课程" << stuSubNum << "个" << std::endl;
			std::cout << "共" << subNum + clsNum + stuNum + stuSubNum << "个" << std::endl;
			SET_TEXT_WARNING();
			std::cout << "失败" << errNum << "个" << std::endl;
			SET_TEXT_NORMAL();
			break;
		}
		case 'L': case 'l':
		{
			std::string fileName;
			std::cout << "请输入您要保存的文件名称: " << std::flush;
			std::getline(std::cin, fileName);
			if (!ChangeInfo::SaveToFile(fileName))
			{
				SET_TEXT_WARNING(); std::cout << "存入文件失败！无法打开文件: " << fileName << std::endl; SET_TEXT_NORMAL();
			}
			else
			{
				SET_TEXT_SUCCESS(); std::cout << "成功存入文件" << fileName << std::endl; SET_TEXT_NORMAL();
			}
			break;
		}
		case 'M': case 'm':
			SET_TEXT_WARNING();
			std::cout << "清空所有数据将无法恢复，您确定要这样做吗?(Y/n): " << std::flush;
			SET_TEXT_NORMAL();
			buf = 0;
			while (true)
			{
				std::cin >> buf;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (buf)
				{
				case 'Y': case 'y':
					ChangeInfo::Clear();
					SET_TEXT_SUCCESS(); std::cout << "已清空所有数据！" << std::flush; SET_TEXT_NORMAL();
					break;
				case 'N': case 'n':
					SET_TEXT_SUCCESS(); std::cout << "已成功取消清空操作！" << std::flush; SET_TEXT_NORMAL();
					break;
				default:
					SET_TEXT_WARNING();
					std::cout << "输入非法！清空所有数据将无法恢复，您确定要这样做吗?(Y/n): " << std::flush;
					SET_TEXT_NORMAL();
					continue;
				}
				break;
			}
			break;
		default:
			std::cout << "无此选项！" << std::endl;
		}
	}
}

void UI::PrintSubject()
{
	if (mode == modeType::optional)
	{
		std::cout << std::endl << "学科清单\n" << separator << std::endl;
		std::cout << std::setw(idLength) << "课程ID|" << std::setw(nameLength) << "课程名称|"
			<< std::setw(scoreLength) << "满分|" << std::setw(5) << "学分" << std::endl;
		for (std::map<basic_info::idType, Subject*>::const_iterator itr = info.GetSubjectList().begin();
			itr != info.GetSubjectList().end(); ++itr)
		{
			std::cout << std::setw(idLength) << itr->first << std::setw(nameLength) << itr->second->GetName() << std::setw(scoreLength) << std::setprecision(2)
				<< itr->second->GetFullScore() << std::setw(5) << std::setprecision(2) << itr->second->GetCredit() << std::endl;
		}
		std::cout << separator << std::endl << std::endl;
	}
	else
	{
		std::cout << "学科清单\n" << separator << std::endl; 
		std::cout << std::setw(idLength) << "课程ID|" << std::setw(nameLength) << "课程名称|"
			<< std::setw(scoreLength) << "满分" << std::endl; 
		for (std::map<basic_info::idType, Subject*>::const_iterator itr = info.GetSubjectList().begin();
			itr != info.GetSubjectList().end(); ++itr)
		{
			std::cout << std::setw(idLength) << itr->first << std::setw(nameLength) << itr->second->GetName() << std::setw(scoreLength) << std::setprecision(2)
				<< itr->second->GetFullScore() << std::endl;
		}
		std::cout << separator << std::endl << std::endl;
	}
}

void UI::PrintStudentInfoHead(bool sortedByScore)
{

	std::cout << std::setw(idLength) << "学生ID|" << std::setw(nameLength) << "姓名|"
		<< std::setw(5) << "性别|" << std::setw(idLength) << "班级ID|" << std::setw(scoreLength) << (mode == modeType::optional ? "均绩|" : "总分");
	if (sortedByScore) std::cout << std::setw(5) << "名次";
	std::cout << std::endl;
	std::cout << std::setw(idLength) << "课程ID|" << std::setw(nameLength) << "课程名称|" << std::setw(scoreLength) << "分数"; 
	if (mode == modeType::optional) std::cout << std::setw(5) << "学分"; 
	std::cout << std::endl;
	std::cout << starSeparator << std::endl;

}

void UI::PrintStudentInfo(Student* pStudent, size_t sortedByScore)
{
	std::cout << std::setw(idLength) << pStudent->GetID() << std::setw(nameLength) << pStudent->GetName()
		<< std::setw(5) << ((pStudent->GetGender() == Student::genderType::male) ? "男" : "女")
		<< std::setw(idLength) << pStudent->GetClassID() << std::setw(scoreLength) << std::setprecision(2) << pStudent->GetValid();
	if (sortedByScore) std::cout << std::setw(5) << sortedByScore;
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = pStudent->GetSubjectList().begin();
		itr != pStudent->GetSubjectList().end(); ++itr)
	{
		std::cout << std::endl << thinSeparator << std::endl;
		std::cout << std::setw(idLength) << itr->first << std::setw(nameLength) << info.GetSubjectList().at(itr->first)->GetName()
			<< std::setw(scoreLength) << std::setprecision(2) << itr->second; 
		if (mode == modeType::optional) std::cout << std::setw(5) << info.GetSubjectList().at(itr->first)->GetCredit(); 
	}
	std::cout << std::endl << starSeparator << std::endl;
}

void UI::PrintStudent(bool sortedByScore)
{
	std::cout << std::endl << "学生成绩单\n" << separator << std::endl;
	PrintStudentInfoHead(sortedByScore); 
	std::multimap<basic_info::scoreType, Student*, std::greater<basic_info::scoreType>> sortStudent;
	size_t count = 0;				//记录名次
	if (sortedByScore)
	{

		//排序
		for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
			itr != info.GetStudentList().end(); ++itr)
		{
			sortStudent.insert(std::pair<basic_info::scoreType, Student*>(itr->second->GetValid(), itr->second));
		}

		//输出
		for (std::multimap<basic_info::scoreType, Student*>::const_iterator itr = sortStudent.begin();
			itr != sortStudent.end(); ++itr)
		{
			PrintStudentInfo(itr->second, ++count);
		}
	}
	else
	{
		for (std::map<basic_info::idType, Student*>::const_iterator itr = info.GetStudentList().begin();
			itr != info.GetStudentList().end(); ++itr)
		{
			PrintStudentInfo(itr->second, 0);
		}
	}
	std::cout << "学生总数: " << info.GetStudentList().size() << std::endl;
	std::cout << separator << std::endl << std::endl;
}

void UI::PrintSubjectStudent(basic_info::idType subjectID, bool sortedByScore)
{
	if (info.GetSubjectList().find(subjectID) == info.GetSubjectList().end())
	{
		std::cout << std::endl << "不存在ID为" << subjectID << "的课程！" << std::endl << std::endl; 
		return; 
	}
	std::cout << std::endl << "学生成绩单\t学科ID: " << subjectID << "\t学科名称: " << info.GetSubjectList().at(subjectID)->GetName()
		<< "\t满分: " << info.GetSubjectList().at(subjectID)->GetFullScore();
	if(mode == modeType::optional) std::cout << "\t学分: " << info.GetSubjectList().at(subjectID)->GetCredit();
	std::cout << std::endl << separator << std::endl; 
	if (sortedByScore)
	{
		std::multimap<basic_info::scoreType, Student*, std::greater<basic_info::scoreType> > sortStudent; 
		size_t count = 0;	//记录名次

		//排序
		for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = info.GetSubjectList().at(subjectID)->GetStudentList().begin();
			itr != info.GetSubjectList().at(subjectID)->GetStudentList().end(); ++itr)
		{
			sortStudent.insert(std::make_pair(itr->second, info.GetStudentList().at(itr->first))); 
		}

		//输出
		std::cout << std::setw(idLength) << "学生ID|" << std::setw(nameLength) << "姓名|"
			<< std::setw(5) << "性别|" << std::setw(idLength) << "班级ID|" << std::setw(scoreLength) << "成绩|" << std::setw(5) << "名次" << std::endl;
		for (std::multimap<basic_info::scoreType, Student*>::iterator itr = sortStudent.begin();
			itr != sortStudent.end(); ++itr)
		{
			std::cout << std::setw(idLength) << itr->second->GetID() << std::setw(nameLength) << itr->second->GetName()
				<< std::setw(5) << itr->second->GetGender() << std::setw(idLength) << itr->second->GetClassID() 
				<< std::setw(scoreLength) << std::setprecision(2) << itr->first << std::setw(5) << ++count << std::endl;
		}
	}
	else
	{
		std::cout << std::setw(idLength) << "学生ID|" << std::setw(nameLength) << "姓名|"
			<< std::setw(5) << "性别|" << std::setw(idLength) << "班级ID|" << std::setw(scoreLength) << "成绩" << std::endl;
		for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = info.GetSubjectList().at(subjectID)->GetStudentList().begin();
			itr != info.GetSubjectList().at(subjectID)->GetStudentList().end(); ++itr)
		{
			std::cout << std::setw(idLength) << itr->first << std::setw(nameLength) << info.GetStudentList().at(itr->first)->GetName()
				<< std::setw(5) << info.GetStudentList().at(itr->first)->GetGender() << std::setw(idLength)
				<< info.GetStudentList().at(itr->first)->GetClassID() << std::setw(scoreLength) << std::setprecision(2) << itr->second << std::endl;
		}
	}
	std::cout << "平均成绩: " << info.GetSubjectList().at(subjectID)->GetAverage() << std::endl; 
	std::cout << separator << std::endl << std::endl; 
}

void UI::PrintClassStudent(basic_info::idType classID, bool sortedByScore)
{
	if (info.GetClassList().find(classID) == info.GetClassList().end())
	{
		std::cout << std::endl << "不存在ID为" << classID << "的班级！" << std::endl << std::endl;
		return;
	}
	std::cout << std::endl << "学生成绩单\t班级ID: " << classID << "\t班级名称: " << info.GetClassList().at(classID)->GetName();
	std::cout << std::endl << separator << std::endl;
	PrintStudentInfoHead(sortedByScore); 
	if (sortedByScore)
	{
		std::multimap<basic_info::scoreType, Student*, std::greater<basic_info::scoreType> > sortStudent;
		size_t count = 0;	//记录名次

		//排序
		for (std::set<basic_info::idType>::const_iterator itr = info.GetClassList().at(classID)->GetStudentList().begin();
			itr != info.GetClassList().at(classID)->GetStudentList().end(); ++itr)
		{
			sortStudent.insert(std::make_pair(info.GetStudentList().at(*itr)->GetValid(), info.GetStudentList().at(*itr)));
		}

		//输出
		for (std::multimap<basic_info::scoreType, Student*>::iterator itr = sortStudent.begin();
			itr != sortStudent.end(); ++itr)
		{
			PrintStudentInfo(itr->second, ++count);
		}
	}
	else
	{
		for (std::set<basic_info::idType>::const_iterator itr = info.GetClassList().at(classID)->GetStudentList().begin();
			itr != info.GetClassList().at(classID)->GetStudentList().end(); ++itr)
		{
			PrintStudentInfo(info.GetStudentList().at(*itr), 0);
		}
	}
	std::cout << "平均成绩: " << info.GetClassList().at(classID)->GetAverage() << std::endl;
	std::cout << separator << std::endl << std::endl;
}

void UI::PrintClass()
{
	std::cout << std::endl << "班级名单" << std::endl << separator << std::endl; 
	std::cout << std::setw(idLength) << "班级ID" << std::setw(nameLength) << "班级名称" << std::setw(scoreLength) << "均分" << std::endl;
	for (std::map<basic_info::idType, Class*>::const_iterator itr = info.GetClassList().begin();
		itr != info.GetClassList().end(); ++itr)
	{
		std::cout << std::setw(idLength) << itr->first << std::setw(nameLength) << itr->second->GetName()
			<< std::setw(scoreLength) << std::setprecision(2) << itr->second->GetAverage() << std::endl;
	}
	std::cout << separator << std::endl << std::endl; 
}
