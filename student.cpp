#include "student.h"

bool Student::InsertSubject(basic_info::idType subjectId, basic_info::scoreType score)
{
	if (subjectList.find(subjectId) != subjectList.end()) return false;			//已经学了这门学科
	subjectList.insert(std::make_pair(subjectId, score)); 
	return true; 
}

bool Student::ChangeScore(basic_info::idType subjectId, basic_info::scoreType score)
{
	if (subjectList.find(subjectId) == subjectList.end()) return false;			//没学过这门学科
	subjectList[subjectId] = score; 
	return true; 
}

bool Student::DeleteSubject(basic_info::idType subjectId)
{
	if (subjectList.find(subjectId) == subjectList.end()) return false;			//没学过这门学科
	subjectList.erase(subjectId); 
	return true; 
}

basic_info::scoreType Student::GetSum() const
{
	basic_info::scoreType sum = 0; 
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = subjectList.begin();
		itr != subjectList.end(); ++itr)
		sum += itr->second; 
	return sum; 
}

basic_info::scoreType Student::GetAverage() const
{
	if (subjectList.empty()) return 0;					//没学过任何课
	basic_info::scoreType sum = 0; 
	int sumCredit = 0; 
	for (std::map<basic_info::idType, basic_info::scoreType>::const_iterator itr = subjectList.begin();
		itr != subjectList.end(); ++itr)
	{
		sum += itr->second * info.GetSubjectList().at(itr->first)->GetCredit(); 
		sumCredit += info.GetSubjectList().at(itr->first)->GetCredit(); 
	}
	return sumCredit ? sum / sumCredit : 0; 
}
