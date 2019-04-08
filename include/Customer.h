#pragma once

#include <vector>
#include <string>
#include "Rental.h"

class Customer
{
private:
 const std::string _name;
 std::vector<Rental*> _rentals;

public:
        Customer(const std::string& name):_name(name) {
	}
	~Customer(void)
	{
		_rentals.clear();
	}

	void addRental(Rental* rental)
	{
		_rentals.push_back(rental);
	}

        const std::string& getName(void)
	{
		return _name;
	}
        std::string statement();
};

