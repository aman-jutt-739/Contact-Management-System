#include"ContactGroup.h"
#include<iostream>
#include<string>

ContactGroup::ContactGroup()
{
	id_size = 0;
	id_count = 0;
	id_list = nullptr;
}

void ContactGroup::set_group_name(std::string group_name)
{
	this->group_name = group_name;
}

void ContactGroup::set_contact_id(int contact_id)
{
	if (id_count >= id_size)
	{
		resize_id_list();
	}
	id_list[id_count] = contact_id;
	id_count++;
}

std::string ContactGroup::get_group_name() const
{
	return group_name;
}


int ContactGroup::show_contacts_id(int id_index) const
{
	return id_list[id_index];
}

int ContactGroup::get_id_count() const
{
	return id_count;
}

void ContactGroup::resize_id_list()
{
	int* temp_obj = new int[id_size];
	for (int i = 0; i < id_count; i++)
	{
		temp_obj[i] = id_list[i];
	}
	delete[]id_list;
	id_list = nullptr;
	id_size *= 2;
	id_list = new int[id_size];
	for (int i = 0; i < id_count; i++)
	{
		id_list[i] = temp_obj[i];
	}
	delete[]temp_obj;
	temp_obj = nullptr;
}

void ContactGroup::set_id_size(int size_of_id)
{
	this->id_size = size_of_id;
	id_list = new int[id_size];
}

void ContactGroup::remove_id(int contact_number)
{
	int id_index = 0;
	for(int i = 0; i < id_count; i++)
	{
		if (contact_number == id_list[i])
		{
			id_index = i;
			break;
		}
	}
	for (int i = id_index; i < id_count - 1; i++)
	{
		id_list[i] = id_list[i + 1];
	}
	id_count--;
}