#pragma once
#include<string>

class ContactGroup
{
public:
	ContactGroup();
	void set_group_name(std::string group_name);
	void set_contact_id(int contact_id);
	std::string get_group_name() const;
	int show_contacts_id(int id_index) const;
	int get_id_count() const;
	void resize_id_list();
	void set_id_size(int size_of_id);
	void remove_id(int contact_number);
private:
	std::string group_name;
	int* id_list;
	int id_size;
	int id_count;
};