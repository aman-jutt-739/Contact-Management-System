#include "Contact.h"
#include"Address.h"
#include<string>

/*
*	Implement a constructor that initializes all the Contact parts, including address. Call the setter to set values
*	as they have the logic to check correct input
*	Declaration is given in Contact.h
*/
Contact::Contact(std::string first_name, std::string last_name, std::string mobile_number, std::string email_address, Address* address)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->mobile_number = mobile_number;
	this->contact_number = contact_number;
	this->email_address = email_address;
	this->search_times = 0;
	this->address = address;
	this->contact_id = unique_id;
	unique_id++;
	second_number = false;
}

Contact::Contact()
{
	this->address = new Address;
	this->contact_id = unique_id;
	search_times = 0;
	unique_id++;
	second_number = false;
}

void Contact::printContact() const
{
	printAddress();
	std::cout << "First name: " << getFirstName() << ", " << "Last name : " << getLastName() << ", " << "Mobile number1: " << getMobileNumber() << ", " << "Email address: " << getEmailAddress() << std::endl;
}
void Contact::printAddress() const
{
	address->print_address();
}

/*
*	Implement getter/setters for all the member variables of Contact. Also declare them in the Contact.h header file
*	In each setter, do not set value if string is empty ("" 0 size).
*   Check in phone number setter, Phone number must be 11 digits
*/
void Contact::setFirstName(std::string first_name)
{
	if (first_name == "")
	{
		return;
	}
	this->first_name = first_name;
}
void Contact::setLastName(std::string last_name)
{
	if (last_name == "")
	{
		return;
	}
	this->last_name = last_name;
}
void Contact::setMobileNumber(std::string mobile_number)
{
	if (mobile_number == "")
	{
		return;
	}
	this->mobile_number = mobile_number;
}
void Contact::setContactNumber(std::string contact_number)
{
	second_number = true;
	this->contact_number = contact_number;
}
void Contact::setEmailAddress(std::string email_address)
{
	if (email_address == "")
	{
		return;
	}
	this->email_address = email_address;
}
void Contact::setHouse(std::string house)
{
	this->address->setHouse(house);
}
void Contact::setStreet(std::string street)
{
	this->address->setStreet(street);
}
void Contact::setCity(std::string city)
{
	this->address->setCity(city);
}
void Contact::setCountry(std::string country)
{
	this->address->setCountry(country);
}

std::string Contact::getFirstName() const
{
	return first_name;
}
std::string Contact::getLastName() const
{
	return last_name;
}
std::string Contact::getMobileNumber() const
{
	return mobile_number;
}
std::string Contact::getContactNumber()
{
	return contact_number;
}
std::string Contact::getEmailAddress() const
{
	return email_address;
}
std::string Contact::getHouse() const
{
	return this->address->getHouse();
}
std::string Contact::getStreet() const
{
	return this->address->getStreet();
}
std::string Contact::getCity() const
{
	return this->address->getCity();
}
std::string Contact::getCountry() const
{
	return this->address->getCountry();
}
int Contact::get_contactID() const
{
	return contact_id;
}

void Contact::printSecondNumber()
{
	if (second_number == true)
	{
		std::cout << "Mobile number: " << getMobileNumber() << "\n";
		std::cout << "Contact number: " << getContactNumber() << "\n";
	}
	else
	{
		std::cout << "This contact has single number! \n";
	}
}

/*
*	Implement the equals function(as declared in header file) that takes a
*   Contact object and checks if it is equal to current object refered by (this pointer).
*   Compare all the attributes.
*   For comparing address of contact you can call the equals function of the Address object;
*   For example: this.address.equals
*/
bool Contact::equals(Contact contact) const
{
	if (first_name != contact.first_name)
	{
		return false;
	}
	if (last_name != contact.last_name)
	{
		return false;
	}
	if (mobile_number != contact.mobile_number)
	{
		return false;
	}
	if (email_address != contact.email_address)
	{
		return false;
	}
	if (contact.address->equals(*address) == false)
	{
		return false;
	}
	return true;
}

Contact* Contact::copy_contact()
{
	/*
		Return a new object(deep copy of "this"[due to Address pointer, which should also be copied])
	*/
	Contact* temp_obj = new Contact;
	temp_obj->setFirstName(this->first_name);
	temp_obj->setLastName(this->last_name);
	temp_obj->setMobileNumber(this->mobile_number);
	temp_obj->setEmailAddress(this->email_address);
	temp_obj->setHouse(this->address->getHouse());
	temp_obj->setStreet(this->address->getStreet());
	temp_obj->setCity(this->address->getCity());
	temp_obj->setCountry(this->address->getCountry());
	return temp_obj;
}

void Contact::setSearchTimes()
{
	search_times++;
}
int Contact::getSearchTime() const
{
	return search_times;
}

int Contact::unique_id = 1;