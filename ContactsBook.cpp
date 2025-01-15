#include "ContactsBook.h"
#include"SearchHistory.h"
#include<fstream>
#include<string>

ContactsBook::ContactsBook(int size_of_list)
{
	/*
	*	Initialize the contacts_list array, also initialize the size and count members accordingly
	*/
	size_of_contacts = size_of_list;
	contacts_list = new Contact[size_of_contacts];
	contacts_count = 0;
	search_obj = new SearchHistory(size_of_list);
	group_var = nullptr;
	group_count = 0;
}

void ContactsBook::add_contact(const Contact& contact)
{
	/*
		- Check if the list is full, if it is full call the resize function
		- If list is not full add the contact to the end of the array
		- (end means the place where last contact was inserted)
		- At start it will be 0th index as no contact has been inserted before so
		- count is zero (contacts_count member)
		- Increment the count
		- As inserted successfully, return 1
	*/
	if (contacts_count >= size_of_contacts)
	{
		resize_list();
		std::cout << "Resize function called! \n";
	}
	contacts_list[contacts_count] = contact;
	contacts_count++;
}

int ContactsBook::get_group_count() const
{
	return group_count;
}

void ContactsBook::display_groups() const
{
	for (int i = 0; i < group_count; i++)
	{
		std::cout << "-----Group " << i + 1 << " details-----\n";
		std::cout << "Group Name: " << group_var[i].get_group_name() << std::endl;
	}
}

int ContactsBook::get_groupContacts(int group_index)
{
	return group_var[group_index - 1].get_id_count();
}

void ContactsBook::display_byID(int id_index) const
{
	for (int i = 0; i < contacts_count; i++)
	{
		if (id_index == contacts_list[i].get_contactID())
		{
			contacts_list[i].printAddress();
			std::cout << "First name: " << contacts_list[i].getFirstName() << " " << "Last name: " << contacts_list[i].getLastName() << " " << "Mobile number: " << contacts_list[i].getMobileNumber() << " " << "Email address: " << contacts_list[i].getEmailAddress() << std::endl;
		}
	}
}

void ContactsBook::add_id(int group_number, int contact_number)
{
	group_var[group_number - 1].set_contact_id(contacts_list[contact_number-1].get_contactID());
	std::cout << "Contact saved to group! \n";
}

void ContactsBook::show_group_contacts(int group_number)
{
	int id_index;
	for (int i = 0; i < group_var[group_number - 1].get_id_count(); i++)
	{
		id_index = group_var[group_number - 1].show_contacts_id(i);
		std::cout << "-----Contact " << i + 1 << " details-----\n";
		display_byID(id_index);
	}
}

void ContactsBook::remove_contact(int group_number, int contact_number)
{
	group_var[group_number - 1].remove_id(contacts_list[contact_number-1].get_contactID());
	std::cout << "Contact removed! \n";
}

void ContactsBook::create_group(std::string group_name)
{
	if (group_count == 0)
	{
		group_var = new ContactGroup[group_count + 1];
		group_var[group_count].set_id_size(size_of_contacts);
		group_var[group_count].set_group_name(group_name);
		group_count++;
	}
	else
	{
		ContactGroup* temp_obj = new ContactGroup[group_count];
		for (int i = 0; i < group_count; i++)
		{
			temp_obj[i] = group_var[i];
		}
		delete[]group_var;
		group_var = nullptr;
		group_var = new ContactGroup[group_count + 1];
		for (int i = 0; i < group_count; i++)
		{
			group_var[i] = temp_obj[i];
		}
		delete[]temp_obj;
		temp_obj = nullptr;
		group_var[group_count].set_group_name(group_name);
		group_var[group_count].set_id_size(size_of_contacts);
		group_count++;
	}
	std::cout << "Group created! \n";
}

void ContactsBook::search_contact_in_groups(int contact_number)
{
	int count = 1;
	for (int i = 0; i < group_count; i++)
	{
		for (int j = 0; j < group_var[i].get_id_count(); j++)
		{
			if (group_var[i].show_contacts_id(j) == contacts_list[contact_number - 1].get_contactID())
			{
				contacts_list[contact_number - 1].setSearchTimes();
				std::cout << "Group " << count << " is: " << group_var[i].get_group_name() << std::endl;
				count++;
			}
		}
	}
}

void ContactsBook::remove_group(int group_number)
{
	for (int i = group_number - 1; i < group_count - 1; i++)
	{
		group_var[i] = group_var[i + 1];
	}
	group_count--;
	std::cout << "Group removed! \n";
}

int ContactsBook::total_contacts()
{
	/*
	*	Return the total contacts currently stored
	*/

	/*
	*	Remove this return -1; before writing your code
	*/
	return contacts_count;
}

bool ContactsBook::full() const
{
	/*
	* Return true if list is full, false otherwise
	*/

	/*
	*	Remove this return false; before writing your code
	*/
	if (contacts_count >= size_of_contacts)
	{
		return true;
	}
	return false;
}

void ContactsBook::resize_list()
{
	/*
	*	Here you will resize the contact list, see example code given in lab manual to see how to resize arrays
	*	You will allocate a temporary new array of double the current size and copy the contacts from
	*       previous array to this array one by one, get the copy of each contact using copy_contact
	*       function of Contact class
	*	Delete the previous array
	*	Assign the new temporary array to the contacts_list pointer
	*	Updated the this->size_of_contacts with new size
	*/
	Contact* temp = new Contact[size_of_contacts];
	copyFunction(temp);
	delete[]contacts_list;
	contacts_list = nullptr;
	size_of_contacts *= 2;
	contacts_list = new Contact[size_of_contacts];
	for (int i = 0; i < contacts_count; i++)
	{
		contacts_list[i] = *temp[i].copy_contact();
	}
	delete[]temp;
	temp = nullptr;
}

void ContactsBook::viewTopSearchContacts()
{
	int top_times, top_index[5], count_var = 0;
	bool flag;
	for (int i = 0; i < contacts_count - 1; i++)
	{
		flag = false;
		if (count_var == 5)
		{
			break;
		}
		for (int k = 0; k < count_var; k++)
		{
			if (i == top_index[k])
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			if (contacts_list[i].getSearchTime() != 0)
			{
				top_times = contacts_list[i].getSearchTime();
				top_index[count_var] = i;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
		for (int j = 0; j < contacts_count; j++)
		{
			flag = false;
			if (top_times < contacts_list[j].getSearchTime())
			{
				for (int k = 0; k < count_var; k++)
				{
					if (j == top_index[k])
					{
						flag = true;
						break;
					}
				}
				if (flag == false)
				{
					top_times = contacts_list[j].getSearchTime();
					top_index[count_var] = j;
				}
			}
		}
		count_var++;
	}
	if (count_var == 0)
	{
		std::cout << "No searched contact! \n";
	}
	else
	{
		std::cout << "Top " << count_var << " searched contacts are: \n";
		for (int i = 0; i < count_var; i++)
		{
			std::cout << "-----Contact " << i + 1 << " details----- \n";
			contacts_list[top_index[i]].printAddress();
			std::cout << "First name: " << contacts_list[top_index[i]].getFirstName() << ", " << "Last name: " << contacts_list[top_index[i]].getLastName() << ", " << "Mobile number: " << contacts_list[top_index[i]].getMobileNumber() << ", " << "Email Address: " << contacts_list[top_index[i]].getEmailAddress() << std::endl;
		}
	}
}

void ContactsBook::viewSearchHistory()
{
	std::cout << "-------Search History-------\n";
	for (int i = search_obj->getSearchCount() - 1; i >= 0; i--)
	{
		search_obj->getHistory(i);
	}
}

void ContactsBook::search_contact_details(std::string contact_info)
{
	bool flag_var = false;
	search_obj->inputHistory(contact_info);
	for (int i = 0; i < contacts_count; i++)
	{
		if (contact_info == contacts_list[i].getFirstName() || contact_info == contacts_list[i].getLastName() || contact_info == contacts_list[i].getMobileNumber() || contact_info == contacts_list[i].getEmailAddress() || contact_info == contacts_list[i].getHouse() || contact_info == contacts_list[i].getStreet() || contact_info == contacts_list[i].getCity() || contact_info == contacts_list[i].getCountry())
		{
			if (flag_var == false)
			{
				std::cout << "The matched contacts are: \n";
			}
			flag_var = true;
			contacts_list[i].setSearchTimes();
			contacts_list[i].printAddress();
			std::cout << "First name: " << contacts_list[i].getFirstName() << ", " << contacts_list[i].getLastName() << ", " << contacts_list[i].getMobileNumber() << ", " << contacts_list[i].getEmailAddress() << std::endl;
		}
	}
	if (flag_var == false)
	{
		std::cout << "No contact with such information is found! \n";
	}
}

void ContactsBook::view_single_contact()
{
	int contact_index;
	for (int i = 0; i < contacts_count; i++)
	{
		std::cout << "-----Contact " << i + 1 << "-----\n";
		std::cout << "First name: " << contacts_list[i].getFirstName() << ", " << "Last name: " << contacts_list[i].getLastName() << std::endl;
	}
	std::cout << "Enter contact no. to view its detail: ";
	std::cin >> contact_index;
	while (contact_index<1 || contact_index>contacts_count)
	{
		std::cout << "Enter valid contact number: ";
		std::cin >> contact_index;
	}
	std::cout << "-----Contact details-----\n";
	contacts_list[contact_index - 1].printAddress();
	std::cout << "First name: " << contacts_list[contact_index - 1].getFirstName() << ", " << "Last name: " << contacts_list[contact_index - 1].getLastName() << ", " << "Mobile number: " << contacts_list[contact_index - 1].getMobileNumber() << ", " << "Email address: " << contacts_list[contact_index - 1].getEmailAddress() << std::endl;
}

void ContactsBook::search_byCharacters(std::string input_byCharacters)
{
	bool flag_var, check_var = false;
	int count_char;
	int size_char = input_byCharacters.size(), size_string;
	for (int i = 0; i < total_contacts(); i++)
	{
		count_char = 0;
		flag_var = false;
		size_string = contacts_list[i].getFirstName().size();
		for (int j = 0; j < size_string; j++)
		{
			if (count_char == size_char)
			{
				flag_var = true;
			}
			if (flag_var == true)
			{
				break;
			}
			if (input_byCharacters[count_char] == contacts_list[i].getFirstName()[j])
			{
				count_char++;
			}
		}
		size_string = contacts_list[i].getLastName().size();
		for (int j = 0; j < size_string; j++)
		{
			if (count_char == size_char)
			{
				flag_var = true;
			}
			if (flag_var == true)
			{
				break;
			}
			if (input_byCharacters[count_char] == contacts_list[i].getLastName()[j])
			{
				count_char++;
			}
		}
		if (flag_var == true)
		{
			check_var = true;
			std::cout << "Information found in contact " << i + 1 << " name! \n";
			std::cout << contacts_list[i].getFirstName() << " " << contacts_list[i].getLastName() << std::endl;
		}
		flag_var = false;
		count_char = 0;
		size_string = contacts_list[i].getMobileNumber().size();
		for (int j = 0; j < size_string; j++)
		{
			if (count_char == size_char)
			{
				flag_var = true;
			}
			if (flag_var == true)
			{
				break;
			}
			if (input_byCharacters[count_char] == contacts_list[i].getMobileNumber()[j])
			{
				count_char++;
			}
		}
		if (flag_var == true)
		{
			std::cout << "Information found in contact " << i + 1 << " mobile number! \n";
			std::cout << contacts_list[i].getMobileNumber() << std::endl;
		}
	}
	if (check_var == false)
	{
		std::cout << "No contact found with such information! \n";
	}
}

void ContactsBook::update_details(int contact_number)
{
	std::string string_var;
	std::cout << "Enter new first name: ";
	std::cin.ignore();
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setFirstName(string_var);
	std::cout << "Enter new last name: ";
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setLastName(string_var);
	std::cout << "Enter new mobile number: ";
	getline(std::cin, string_var);
	while (string_var.size() != 11)
	{
		std::cout << "Enter 11 digits number: ";
		getline(std::cin, string_var);
	}
	contacts_list[contact_number - 1].setMobileNumber(string_var);
	std::cout << "Enter new email address: ";
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setEmailAddress(string_var);
	std::cout << "Enter new house number: ";
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setHouse(string_var);
	std::cout << "Enter new street number: ";
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setStreet(string_var);
	std::cout << "Enter new city name: ";
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setCity(string_var);
	std::cout << "Enter new country name: ";
	getline(std::cin, string_var);
	contacts_list[contact_number - 1].setCountry(string_var);
	std::cout << "Contact updated! \n";
}

void ContactsBook::delete_contact(int contact_number)
{
	for (int i = contact_number - 1; i < contacts_count - 1; i++)
	{
		contacts_list[i] = contacts_list[i + 1];
	}
	contacts_count--;
	std::cout << "Contact deleted! \n";
}

void ContactsBook::copyFunction(Contact* contact_obj)
{
	for (int i = 0; i < contacts_count; i++)
	{
		contact_obj[i] = *contacts_list[i].copy_contact();
	}
}

void ContactsBook::printContact() const
{
	for (int i = 0; i < contacts_count; i++)
	{
		std::cout << "-----Contact " << i + 1 << " details-----\n";
		contacts_list[i].printContact();
	}
}

void ContactsBook::print_contacts_sorted(std::string choice)
{
	/*
	*	Create a copy of this->contacts_list array here (do it by creating a new function that returns copy)
	*	Call the sort function sort_contacts_list to sort the newly created copy
	*	This copy is created to avoid changing the original insertion order of contact list
	*	Then print the contacts in following format:
	*	[First Name] [Last Name] [Mobile] [Email]
	*	Call the address print function to print address on next line
	*/
	Contact* temp_obj = new Contact[size_of_contacts];
	copyFunction(temp_obj);
	sort_contacts_list(temp_obj, choice);
	for (int i = 0; i < contacts_count; i++)
	{
		std::cout << "-----Contact " << i + 1 << " details-----\n";
		temp_obj[i].printAddress();
		std::cout << "First name: " << temp_obj[i].getFirstName() << ", " << "Last name: " << temp_obj[i].getLastName() << ", " << "Mobile number: " << temp_obj[i].getMobileNumber() << ", " << "Email address: " << temp_obj[i].getEmailAddress() << std::endl;
	}
	delete[]temp_obj;
	temp_obj = nullptr;
}

void ContactsBook::sort_contacts_list(Contact* contacts_list, std::string choice)
{
	/*
		You should not duplicate the code to sort based on choices
		Follow the strategy provided in manual/tutorial to avoid duplicating the code (Section B & E only)
		Sort by the fist letter of first name or last name as given in choice
	*/
	if (choice == "first")
	{
		for (int i = 0; i < contacts_count - 1; i++)
		{
			for (int j = i + 1; j < contacts_count; j++)
			{
				if (contacts_list[i].getFirstName() > contacts_list[j].getFirstName())
				{
					Contact* var1, * var2;
					var1 = contacts_list[i].copy_contact();
					var2 = contacts_list[j].copy_contact();
					contacts_list[i] = *var2;
					contacts_list[j] = *var1;
				}
			}
		}
	}
	else if (choice == "last")
	{
		for (int i = 0; i < contacts_count - 1; i++)
		{
			for (int j = i + 1; j < contacts_count; j++)
			{
				if (contacts_list[i].getLastName() > contacts_list[j].getLastName())
				{
					Contact* var1, * var2;
					var1 = contacts_list[i].copy_contact();
					var2 = contacts_list[j].copy_contact();
					contacts_list[i] = *var2;
					contacts_list[j] = *var1;
				}
			}
		}
	}
	else
	{
		contacts_list = nullptr;
	}
}

void ContactsBook::merge_duplicates()
{
	// Implement this function that finds and merges all the duplicates
	// Duplicate means exact equal
	// If there are three copies of a Contact, then only one should remain
	// For example: If total contact are 10, and 2 contacts are same, after removing duplicates
	// 9 contacts will be left; and the this->contacts_count of list will 9
	// At the end display contacts merged, and count of merged contacts
	int count = 0;
	for (int i = 0; i < contacts_count - 1; i++)
	{
		for (int j = i + 1; j < contacts_count; j++)
		{
			if (contacts_list[i].equals(contacts_list[j]))
			{
				for (int k = j; k < contacts_count - 1; k++)
				{
					contacts_list[k] = contacts_list[k + 1];
				}
				count++;
			}
		}
	}
	this->contacts_count -= count;
	std::cout << "Merging process complete! \n";
}


void ContactsBook::load_from_file(std::string file_name)
{
	/*
	*	Read contacts back from file in the same format
	*	Read the contacts_count, and run a loop for this contacts_count and read the
	*	contacts in the same format as you stored
	*	Add them to contact book (this.add_contact function can be used)
	*	Finally, close the file
	*/
	std::ifstream read_var;
	read_var.open(file_name + ".txt");
	if (read_var.is_open())
	{
		while (!read_var.eof())
		{
			Contact contact_var;
			int count_var;
			std::string temp_var, newTemp_var1[4], newTemp_var2[4], concatenate_string;
			int string_index, newString_index, array_index;
			read_var >> count_var;
			for (int i = 0; i < count_var; i++)
			{
				read_var >> temp_var;
				string_index = 0;
				array_index = 0;
				for (int j = 0; j < temp_var.size(); j++)
				{
					if (temp_var[j] == ',')
					{
						newString_index = j;
						for (int k = string_index; k < newString_index; k++)
						{
							if (k == string_index)
							{
								concatenate_string = temp_var[k];
							}
							else
							{
								concatenate_string = concatenate_string + temp_var[k];
							}
						}
						string_index = newString_index + 1;
						newTemp_var1[array_index] = concatenate_string;
						array_index++;
					}
					else if (j == temp_var.size() - 1)
					{
						newString_index = j + 1;
						for (int k = string_index; k < newString_index; k++)
						{
							if (k == string_index)
							{
								concatenate_string = temp_var[k];
							}
							else
							{
								concatenate_string = concatenate_string + temp_var[k];
							}
						}
						string_index = newString_index + 1;
						newTemp_var1[array_index] = concatenate_string;
						array_index++;
					}
				}
				read_var >> temp_var;
				string_index = 0;
				array_index = 0;
				for (int j = 0; j < temp_var.size(); j++)
				{
					if (temp_var[j] == ',')
					{
						newString_index = j;
						for (int k = string_index; k < newString_index; k++)
						{
							if (k == string_index)
							{
								concatenate_string = temp_var[k];
							}
							else
							{
								concatenate_string = concatenate_string + temp_var[k];
							}
						}
						string_index = newString_index + 1;
						newTemp_var2[array_index] = concatenate_string;
						array_index++;
					}
					else if (j == temp_var.size() - 1)
					{
						newString_index = j + 1;
						for (int k = string_index; k < newString_index; k++)
						{
							if (k == string_index)
							{
								concatenate_string = temp_var[k];
							}
							else
							{
								concatenate_string = concatenate_string + temp_var[k];
							}
						}
						string_index = newString_index + 1;
						newTemp_var2[array_index] = concatenate_string;
						array_index++;
					}
				}
				contact_var.setFirstName(newTemp_var1[0]);
				contact_var.setLastName(newTemp_var1[1]);
				contact_var.setMobileNumber(newTemp_var1[2]);
				contact_var.setEmailAddress(newTemp_var1[3]);
				contact_var.setHouse(newTemp_var2[0]);
				contact_var.setStreet(newTemp_var2[1]);
				contact_var.setCity(newTemp_var2[2]);
				contact_var.setCountry(newTemp_var2[3]);
				add_contact(contact_var);
			}
			break;
		}
		read_var.close();
		std::cout << "Read from file process completed! \n";
	}
	else
	{
		std::cout << "Error in opening file! \n";
	}
}


void ContactsBook::save_to_file(std::string file_name)
{
	/*
	*	In this function you will store all the contacts to a file
	*	On first line store contacts_count
	*	On next lines store contacts in the following format:
	*       2 lines for each contact
	*       On oneline write contact attributes(except address) in comma separated format. On second line
	*	store address atributes in the same format
	*	first_name,last_name,mobile_number,email_address
	*	house,street,city,country
	*	Close the file
	*/
	std::ofstream write_var;
	write_var.open(file_name + ".txt");
	if (write_var.is_open())
	{
		write_var << contacts_count << std::endl;
		for (int i = 0; i < contacts_count; i++)
		{
			write_var << contacts_list[i].getFirstName() << "," << contacts_list[i].getLastName() << "," << contacts_list[i].getMobileNumber() << "," << contacts_list[i].getEmailAddress() << std::endl;
			write_var << contacts_list[i].getHouse() << "," << contacts_list[i].getStreet() << "," << contacts_list[i].getCity() << "," << contacts_list[i].getCountry() << std::endl;
		}
		write_var.close();
		std::cout << "Data saved to file! \n";
	}
	else
	{
		std::cout << "Error in opening file! \n";
	}
}

void ContactsBook::addSecond(int index, std::string contact_number)
{
	contacts_list[index - 1].setContactNumber(contact_number);
}
void ContactsBook::printSecond(int index)
{
	contacts_list[index - 1].printSecondNumber();
}