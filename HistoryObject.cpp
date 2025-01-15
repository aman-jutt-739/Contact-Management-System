#include"HistoryObject.h"

void HistoryObject::setSearchWords(std::string search_words)
{
	this->search_words = search_words;
}

void HistoryObject::setTimeDate()
{
	time_date = time(0);
	localtime_s(&get_time, &time_date);
}

std::string HistoryObject::getSearchWords() const
{
	return search_words;
}

tm HistoryObject::getTimeDate() const
{
	return get_time;
}