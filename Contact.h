#pragma once

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>
#include <string>
#endif // !BASIC_LIB

#include "Address.h"


class Contact {
private:
	std::string first_name;
	std::string last_name;
	std::string mobile_number;
	std::string contact_number;
	std::string email_address;
	Address* address;
	int search_times;
	int contact_id;
	static int unique_id;
	bool second_number;
public:
	bool equals(Contact contact) const;
	Contact* copy_contact();

	Contact();
	Contact(std::string first_name, std::string last_name, std::string mobile_number, std::string email_address, Address* address);

	friend std::istream& operator >> (std::istream& in, Contact& contact_obj);

	void printContact() const;
	void printAddress() const;

	void setFirstName(std::string first_name);
	void setLastName(std::string last_name);
	void setMobileNumber(std::string mobile_number);
	void setContactNumber(std::string contact_number);
	void setEmailAddress(std::string email_address);
	void setHouse(std::string house);
	void setStreet(std::string street);
	void setCity(std::string city);
	void setCountry(std::string country);

	void setSearchTimes();
	int getSearchTime() const;
	void printSecondNumber();

	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getMobileNumber() const;
	std::string getContactNumber();
	std::string getEmailAddress() const;
	std::string getHouse() const;
	std::string getStreet() const;
	std::string getCity() const;
	std::string getCountry() const;
	int get_contactID() const;
};