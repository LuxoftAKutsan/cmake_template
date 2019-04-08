#include "Customer.h"
#include <sstream>

std::string Customer::statement() {
  std::stringstream result;
	double totalAmount = 0;
	int frequentRenterPoints = 0;
	std::vector<Rental*>::iterator rentals = _rentals.begin();

  result << "Rent for " + getName() << std::endl;
	while(rentals != _rentals.end())
	{
		double thisAmount = 0;
		Rental* each = *rentals;
    //Summ for each row
		switch(each->getMovie()->getPriceCode())
		{
		case Movie::REGULAR:
			thisAmount+=2;
			if(each->getDaysRented() > 2)
				thisAmount+=(each->getDaysRented()- 2) * 15;
			break;
		case Movie::NEW_RELEASE:
			thisAmount += each->getDaysRented() * 3;
		    break;
		case Movie::CHILDREN:
			thisAmount+=15;
			if(each->getDaysRented() > 3)
				thisAmount += (each->getDaysRented() -3)*15;
			break;
		}
    // Add points for active renter
		frequentRenterPoints++;
    // Bonus for 2 days rent
		if(each->getMovie()->getPriceCode() == Movie::NEW_RELEASE && each->getDaysRented() > 1)
			frequentRenterPoints++;
    // Show rent results
    result << "\t" << each->getMovie()->getTitle() << "\t" << thisAmount << std::endl;
		totalAmount+=thisAmount;
		rentals++;
	}

  // Add footer
  result << "Total : " << totalAmount << std::endl;
  result << "Bonus points  : " << frequentRenterPoints << std::endl;
  return result.str();
}
