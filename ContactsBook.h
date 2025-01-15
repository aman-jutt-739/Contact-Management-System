#pragma once
#include "Contact.h"
#include"SearchHistory.h"
#include"ContactGroup.h"

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>
#include <string>
#endif // !BASIC_LIB


class ContactsBook {
private:
	ContactGroup* group_var;
	int group_count;
	SearchHistory* search_obj;
	Contact* contacts_list; // array of contacts
	int size_of_contacts;   // storage limit
	int contacts_count;     // total contacts currently stored, next contact will be 
	// stored at this count plus 1 index

public:
	void add_contact(const Contact& contact);
	int total_contacts();

	int get_group_count() const;
	void display_groups() const;
	void display_byID(int id_index) const;
	void add_id(int group_number, int contact_number);
	void show_group_contacts(int group_number);
	void remove_contact(int group_number, int contact_number);
	void search_contact_in_groups(int contact_number);
	void remove_group(int group_number);
	void create_group(std::string group_name);
	int get_groupContacts(int group_index);

	void viewSearchHistory();
	void viewTopSearchContacts();
	void view_single_contact();

	void search_byCharacters(std::string input_characters);
	void search_contact_details(std::string contact_info);
	void update_details(int contact_number);
	void delete_contact(int contact_number);

	ContactsBook(int size_of_list);

	void copyFunction(Contact* contact_obj);

	void addSecond(int index, std::string contact_number);
	void printSecond(int index);

	void printContact() const;
	void print_contacts_sorted(std::string choice); // Only two choices first_name or last_name
	void merge_duplicates(); // Implement this function that finds and merges all the duplicates
	// Duplicate means exact equal, this means if

/*
*  This function loads contacts from the given file (see details in ContactsBook.cpp)
*/
	void load_from_file(std::string file_name);
	void save_to_file(std::string file_name);

private:
	bool full() const;
	void resize_list();
	void sort_contacts_list(Contact* contacts_list, std::string choice);
};