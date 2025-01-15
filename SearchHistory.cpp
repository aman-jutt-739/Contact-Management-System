#include<iostream>
#include"SearchHistory.h"

SearchHistory::SearchHistory(int search_size)
{
	this->search_size = search_size;
	search_history = new HistoryObject[search_size];
	search_count = 0;
}

void SearchHistory::inputHistory(std::string search_sentence)
{
	if (search_count >= search_size)
	{
		resizeObj();
	}
	search_history[search_count].setSearchWords(search_sentence);
	search_history[search_count].setTimeDate();
	search_count++;
}

void SearchHistory::getHistory(int search_index)
{
	tm search_time = search_history[search_index].getTimeDate();
	std::cout << "-----Search no. " << search_index + 1 << "-----\n";
	std::cout << "Time: " << search_time.tm_hour << "/" << search_time.tm_min << "/" << search_time.tm_sec << std::endl;
	std::cout << "Date: " << search_time.tm_mday << "/" << search_time.tm_mon + 1 << "/" << search_time.tm_year + 1900 << std::endl;
	std::cout << "Search string: " << search_history[search_index].getSearchWords() << std::endl;
}

void SearchHistory::resizeObj()
{
	HistoryObject* temp_obj = new HistoryObject[search_size];
	for (int i = 0; i < search_count; i++)
	{
		temp_obj[i] = search_history[i];
	}
	delete[]search_history;
	search_history = nullptr;
	search_size *= 2;
	search_history = new HistoryObject[search_size];
	for (int i = 0; i < search_count; i++)
	{
		search_history[i] = temp_obj[i];
	}
	delete[]temp_obj;
	temp_obj = nullptr;
}

int SearchHistory::getSearchCount()
{
	return search_count;
}