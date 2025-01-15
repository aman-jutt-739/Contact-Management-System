/*
*   Include all the needed headers here to run the scenarios
*/
#include<iostream>
#include<string>
#include"Address.h"
#include"Contact.h"
#include"ContactsBook.h"

std::istream& operator >> (std::istream& in, Contact& contact_obj)
{
	const int obj_limit = 8;
	std::string contact_input[obj_limit], contact_display[obj_limit] = { "Enter first name: ", "Enter last name: ","Enter mobile number: ","Enter email address: ","Enter house number: ", "Enter street number: ","Enter city name: ","Enter country name: " };
	for (int i = 0; i < obj_limit; i++)
	{
		std::cout << contact_display[i];
		if (i == 0)
		{
			in.ignore();
		}
		if (i == 2)
		{
			getline(in, contact_input[i]);
			while (contact_input[i].size() != 11)
			{
				std::cout << "Enter 11 digits number: ";
				getline(in, contact_input[i]);
			}
		}
		if (i != 2)
		{
			getline(in, contact_input[i]);
		}
	}
	contact_obj.first_name = contact_input[0];
	contact_obj.last_name = contact_input[1];
	contact_obj.mobile_number = contact_input[2];
	contact_obj.email_address = contact_input[3];
	contact_obj.setHouse(contact_input[4]);
	contact_obj.setStreet(contact_input[5]);
	contact_obj.setCity(contact_input[6]);
	contact_obj.setCountry(contact_input[7]);
	return in;
}

Address* inputAddress(std::string address_display[], std::string address_input[])
{
	Address* temp_obj = new Address;
	for (int i = 0; i < 4; i++)
	{
		std::cout << address_display[i];
		getline(std::cin, address_input[i]);
	}
	temp_obj->setHouse(address_input[0]);
	temp_obj->setStreet(address_input[1]);
	temp_obj->setCity(address_input[2]);
	temp_obj->setCountry(address_input[3]);
	return temp_obj;
}

Contact* inputContact(std::string contact_display[], std::string contact_input[], std::string address_diplay[], std::string address_input[])
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << contact_display[i];
		if (i == 0)
		{
			std::cin.ignore();
		}
		if (i == 2)
		{
			getline(std::cin, contact_input[i]);
			while (contact_input[i].size() != 11)
			{
				std::cout << "Enter 11 digit number: ";
				getline(std::cin, contact_input[i]);
			}
		}
		if (i != 2)
		{
			getline(std::cin, contact_input[i]);
		}
	}
	Address* address_obj = new Address;
	address_obj = inputAddress(address_diplay, address_input);
	Contact* contact_obj = new Contact(contact_input[0], contact_input[1], contact_input[2], contact_input[3], address_obj);
	return contact_obj;
}

int main()
{
	const int choice_limit = 22, contact_limit = 8, display_limit = 4, address_limit = 4;
	std::string user_choices[choice_limit] = { "0. Exit","1. Add New Contact", "2. Merge Duplicates","3. Store To File","4. Load From File","5. Print Contacts Sorted","6. Print Contacts","7. Display Count Of Contacts","8. Select any contact to get its information(Feature ID 1)","9. Update details of a single contact(Feature ID 2)" ,"10. Delete a single contact(Feature ID 3)", "11. View Search History(feature ID 4)","12. View top 5 searched contacts(Feature ID 5)","13. Create a group(Feature ID 6)","14. Add a contact to the group(Feature ID 7)","15. Remove a contact from a group(Feature ID 8)","16. View a contact's group(Feature ID 9)","17. Delete a group(Feature ID 10)", "18. Enter any information o find it in all contacts(Feature ID 11)", "19. Enter any characters to find it in order in contacts(Feature ID 12)", "20. Add second contact", "21. Display second contact"}, contact_display[display_limit] = {"Enter first name: ", "Enter last name: ","Enter mobile number: ","Enter email address: "}, address_display[display_limit] = {"Enter house number: ", "Enter street number: ","Enter city name: ","Enter country name: "}, contact_input[contact_limit], address_input[address_limit], file_name, first_name, last_name, string_name;
	int input_choice, obj_size, contact_number, group_selection;
	ContactsBook* contacts_list;
	Address* address_obj;
	Contact contact_obj, * search_contact;

	std::cout << "Enter size for ContactsBook object: ";
	std::cin >> obj_size;
	while (!std::cin)
	{
		std::cout << "Enter valid input stream: ";
		std::cin.clear();
		std::cin.ignore();
		std::cin >> obj_size;
	}
	contacts_list = new ContactsBook(obj_size);

	do
	{
		std::cout << "\n\n";
		for (int i = 0; i < choice_limit; i++)
		{
			std::cout << user_choices[i] << std::endl;
		}
		std::cout << "Enter your choice: ";
		std::cin >> input_choice;
		switch (input_choice)
		{
		case 0:
			std::cout << "Exiting! \n";
			break;
		case 1:
			std::cout << "-----Entering contact no. " << contacts_list->total_contacts() + 1 << "-----\n";
			std::cin >> contact_obj;
			contacts_list->add_contact(contact_obj);
			std::cout << "-----Contact added-----\n";
			break;
		case 2:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->merge_duplicates();
			}
			break;
		case 3:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				std::cout << "Enter file name: ";
				std::cin.ignore();
				getline(std::cin, file_name);
				contacts_list->save_to_file(file_name);
			}
			break;
		case 4:
			std::cout << "Enter file name: ";
			std::cin.ignore();
			getline(std::cin, file_name);
			contacts_list->load_from_file(file_name);
			break;
		case 5:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				std::cout << "Enter first or last for sorting display by first name or last name: ";
				std::cin.ignore();
				std::cin >> string_name;
				contacts_list->print_contacts_sorted(string_name);
			}
			break;
		case 6:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->printContact();
			}
			break;
	    case 7:
			std::cout << "Total number of contacts: ";
			std::cout << contacts_list->total_contacts() << std::endl;
			break;
		case 8:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->view_single_contact();
			}
			break;
		case 9:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->printContact();
				std::cout << "Enter contact number for updatation: ";
				std::cin >> contact_number;
				while (contact_number < 1 || contact_number > contacts_list->total_contacts())
				{
					std::cout << "Enter valid contact number: ";
					std::cin >> contact_number;
				}
				contacts_list->update_details(contact_number);
			}
			break;
		case 10:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->printContact();
				std::cout << "Enter contact number for delete it: ";
				std::cin >> contact_number;
				while (contact_number < 1 || contact_number > contacts_list->total_contacts())
				{
					std::cout << "Enter valid contact number: ";
					std::cin >> contact_number;
				}
				contacts_list->delete_contact(contact_number);
			}
			break;
		case 11:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->viewSearchHistory();
			}
			break;
		case 12:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->viewTopSearchContacts();
			}
			break;
		case 13:
			std::cout << "Enter group name: ";
			std::cin.ignore();
			getline(std::cin, string_name);
			contacts_list->create_group(string_name);
			break;
		case 14:
			if (contacts_list->get_group_count() == 0)
			{
				std::cout << "Create groups first! \n";
			}
			else
			{
				contacts_list->display_groups();
				std::cout << "Enter group number: ";
				std::cin >> group_selection;
				while (group_selection<1 || group_selection>contacts_list->get_group_count())
				{
					std::cout << "Enter valid group number: ";
					std::cin >> group_selection;
				}
				if (contacts_list->total_contacts() == 0)
				{
					std::cout << "No contact exist! \n";
				}
				else
				{
					contacts_list->printContact();
					std::cout << "Enter contact number: ";
					std::cin >> contact_number;
					while (contact_number<1 || contact_number>contacts_list->total_contacts())
					{
						std::cout << "Enter valid contact number: ";
						std::cin >> contact_number;
					}
					contacts_list->add_id(group_selection, contact_number);
				}
			}
			break;
		case 15:
			if (contacts_list->get_group_count() == 0)
			{
				std::cout << "No group exist! \n";
			}
			else
			{
				contacts_list->display_groups();
				std::cout << "Enter group number: ";
				std::cin >> group_selection;
				while (group_selection<1 || group_selection>contacts_list->get_group_count())
				{
					std::cout << "Enter valid group number: ";
					std::cin >> group_selection;
				}
				if (contacts_list->get_groupContacts(group_selection) == 0)
				{
					std::cout << "No contact exist in this group! \n";
				}
				else
				{
					contacts_list->show_group_contacts(group_selection);
					std::cout << "Enter contact number: ";
					std::cin >> contact_number;
					while (contact_number<0 || contact_number>contacts_list->total_contacts())
					{
						std::cout << "Enter valid contact number: ";
						std::cin >> contact_number;
					}
					contacts_list->remove_contact(group_selection, contact_number);
				}
			}
			break;
		case 16:
			if (contacts_list->get_group_count() == 0)
			{
				std::cout << "No group exist! \n";
			}
			else
			{
				if (contacts_list->total_contacts() == 0)
				{
					std::cout << "No contact exists! \n";
				}
				else
				{
					contacts_list->printContact();
					std::cout << "Enter contact number: ";
					std::cin >> contact_number;
					while (contact_number<1 || contact_number>contacts_list->total_contacts())
					{
						std::cout << "Enter valid contact number: ";
						std::cin >> contact_number;
					}
					contacts_list->search_contact_in_groups(contact_number);
				}
			}
			break;
		case 17:
			if (contacts_list->get_group_count() == 0)
			{
				std::cout << "No group exist! \n";
			}
			else
			{
				contacts_list->display_groups();
				std::cout << "Enter group number: ";
				std::cin >> group_selection;
				while (group_selection<1 || group_selection>contacts_list->get_group_count())
				{
					std::cout << "Enter valid group number: ";
					std::cin >> group_selection;
				}
				contacts_list->remove_group(group_selection);
			}
			break;
		case 18:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				std::cout << "Enter any inforamtion of contact to find it: ";
				std::cin.ignore();
				getline(std::cin, string_name);
				contacts_list->search_contact_details(string_name);
			}
			break;
		case 19:
			if (contacts_list->total_contacts() == 0)
			{
			    std::cout << "No contact found! \n";
			}
			else
			{
				std::cout << "Enter characters: ";
				std::cin >> string_name;
				contacts_list->search_byCharacters(string_name);
			}
			break;
		case 20:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->printContact();
				std::cout << "Enter contact number: ";
				std::cin >> contact_number;
				while (contact_number<1 || contact_number>contacts_list->total_contacts())
				{
					std::cout << "Enter valid number: ";
					std::cin >> contact_number;
				}
				std::cout << "Enter number: ";
				std::cin.ignore();
				std::cin >> string_name;
				contacts_list->addSecond(contact_number, string_name);
			}
			break;
		case 21:
			if (contacts_list->total_contacts() == 0)
			{
				std::cout << "No contact found! \n";
			}
			else
			{
				contacts_list->printContact();
				std::cout << "Enter contact number: ";
				std::cin >> contact_number;
				while (contact_number<1 || contact_number>contacts_list->total_contacts())
				{
					std::cout << "Enter valid number: ";
					std::cin >> contact_number;
				}
				contacts_list->printSecond(contact_number);
			}
			break;
		default:
			std::cout << "Invalid Choice! \n";
		}
	} while (input_choice != 0);
	delete contacts_list;
	contacts_list = nullptr;
	system("pause");
	return 0;
}