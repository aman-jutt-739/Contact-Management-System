#pragma once
#include <iostream>
#include <string>

class Address {
private:
	std::string house;
	std::string street;
	std::string city;
	std::string country;

public:
	bool equals(const Address& address) const;
	void print_address() const;
	Address copy_address();

	Address(std::string house, std::string street, std::string city, std::string country);
	Address() {}

	void setHouse(std::string house);
	void setStreet(std::string street);
	void setCity(std::string city);
	void setCountry(std::string country);

	std::string getHouse() const;
	std::string getStreet() const;
	std::string getCity() const;
	std::string getCountry() const;
};