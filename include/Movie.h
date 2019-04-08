#pragma once
#include <string>


class Movie
{
private:
        std::string _title;
	int _priceCode;

public:

   enum PriceCodeType
   {
	   CHILDREN,
	   REGULAR,
	   NEW_RELEASE
   };
        Movie(const std::string& title,int priceCode): _title(title),_priceCode(priceCode)
	{

	}
	
	int getPriceCode(void)
	{
		return _priceCode;
	}

	void setPriceCode(int priceCode)
	{
		_priceCode = priceCode;
	}
        std::string getTitle()
	{
		return _title;
	}
};

