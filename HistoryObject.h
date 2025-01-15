#pragma once
#include<string>
#include<ctime>
class HistoryObject
{
public:
	void setSearchWords(std::string);
	void setTimeDate();
	std::string getSearchWords() const;
	tm getTimeDate() const;
private:
	std::string search_words;
	time_t time_date;
	tm get_time;
};