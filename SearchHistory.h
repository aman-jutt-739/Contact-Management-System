#pragma once
#include"HistoryObject.h"
class SearchHistory
{
public:
	SearchHistory(int);
	void inputHistory(std::string);
	int getSearchCount();
	void getHistory(int);
	void resizeObj();
private:
	HistoryObject* search_history;
	int search_size;
	int search_count;
};