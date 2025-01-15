#include "Address.h"


/*
*	Implement a constructor that initializes all the address parts
*
*/
Address::Address(std::string house, std::string street, std::string city, std::string country)
{
	this->house = house;
	this->street = street;
	this->city = city;
	this->country = country;
}

/*
*	Implement getter/setters for all the member variables of Address. Also declare them in the Address.h header file
*
*/
void Address::setHouse(std::string house)
{
	this->house = house;
}
void Address::setStreet(std::string street)
{
	this->street = street;
}
void Address::setCity(std::string city)
{
	this->city = city;
}
void Address::setCountry(std::string country)
{
	this->country = country;
}

std::string Address::getHouse() const
{
	return house;
}
std::string Address::getStreet() const
{
	return street;
}
std::string Address::getCity() const
{
	return city;
}
std::string Address::getCountry() const
{
	return country;
}

/*
*	Implement the equals function that takes an Address object and checks if it is equal to
*	current object refered by (this pointer)
*	Two addresses are equal if all the attributes of addresses are equal
*/
bool Address::equals(const Address& address) const
{
	/*
	* Todo
	*/
	if (this->house != address.house)
	{
		return false;
	}
	if (this->street != address.street)
	{
		return false;
	}
	if (this->city != address.city)
	{
		return false;
	}
	if (this->country != address.country)
	{
		return false;
	}
	return true;
}

void Address::print_address() const
{
	/*
	*	Print address on one line as
	*	House, Street, City, Country
	*/
	std::cout << "House# " << this->house << ", " << "Street# " << this->street << ", " << "City: " << this->city << ", " << "Country: " << this->country << std::endl;
}

Address Address::copy_address()
{
	/*
		return a copy of this
	*/
	Address temp;
	temp.house = this->house;
	temp.street = this->street;
	temp.city = this->city;
	temp.country = this->country;
	return temp;
}