#include <locale.h>
#include "Movie.h"
#include "Customer.h"
#include <iostream>

int main() {
  Movie movie1("Dambo",Movie::CHILDREN);
  Movie movie2("Pet Semetary",Movie::REGULAR);
  Movie movie3("Avengers: Endgame", Movie::NEW_RELEASE);

  Rental rio2(&movie1,3);
  Rental elki2(&movie2,4);
  Rental grandHotel(&movie3,10);

  Customer customer("Videoman");
  customer.addRental(&rio2);
  customer.addRental(&elki2);
  customer.addRental(&grandHotel);

  auto result =  customer.statement();
  std::cout << result << std::endl;

	return 0;
}
