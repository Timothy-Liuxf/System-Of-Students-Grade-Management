
////////////////////////////////////////
//
//  已经弃用的代码
//



//
//class ClassPtr									//Class过大，使用指针减小时间开销
//{
//public:
//	ClassPtr(basic_info::idType id, const std::string& name)
//	{
//		_class = new Class(id, name);
//	}
//
//	ClassPtr(const ClassPtr& src)
//	{
//		_class = new Class(*src._class);
//	}
//
//	ClassPtr& operator=(const ClassPtr& src)
//	{
//		delete _class;
//		_class = new Class(*src._class);
//	}
//
//	//指针操作
//	Class* operator->() { return _class; }
//
//
//	//比较指向的学科大小
//	bool operator<(const ClassPtr& cmp) { return *_class < *cmp._class; }
//
//	~ClassPtr() { delete _class; }
//
//private:
//	Class* _class;
//};
//
//
//
//
//
//class StudentPtr									//Student过大，使用指针减小时间和空间开销
//{
//public:
//	StudentPtr(basic_info::idType id, const std::string& name, People::genderType gender, basic_info::idType classId)
//	{
//		_student = new Student(id, name, gender, classId);
//	}
//
//	StudentPtr(const StudentPtr& src)
//	{
//		_student = new Student(*src._student);
//	}
//
//	StudentPtr& operator=(const StudentPtr& src)
//	{
//		delete _student;
//		_student = new Student(*src._student);
//	}
//
//	//指针操作
//	Student* operator->() { return _student; }
//
//
//	//比较指向的学科大小
//	bool operator<(const StudentPtr& cmp) { return *_student < *cmp._student; }
//
//	~StudentPtr() { delete _student; }
//
//private:
//	Student* _student;
//};
//
//
//
//
//class SubjectPtr									//Subject过大，使用指针减小时间开销
//{
//public:
//	SubjectPtr(basic_info::idType id, const std::string& name, int credit = 1)
//	{
//		_subject = new Subject(id, name, credit);
//	}
//
//	SubjectPtr(const SubjectPtr& src)
//	{
//		_subject = new Subject(*src._subject);
//	}
//
//	SubjectPtr& operator=(const SubjectPtr& src)
//	{
//		delete _subject;
//		_subject = new Subject(*src._subject);
//	}
//
//	//指针操作
//	Subject* operator->() { return _subject; }
//
//
//	//比较指向的学科大小
//	bool operator<(const SubjectPtr& cmp) { return *_subject < *cmp._subject; }
//
//	~SubjectPtr() { delete _subject; }
//
//private:
//	Subject* _subject;
//};
//
//
//
