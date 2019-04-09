#ifndef ICALCULATOR_H
#define ICALCULATOR_H

#include <string>

class ICalculator
{
    public:
        virtual ~ICalculator() = default;

        virtual double calculate(const ::std::string& argument) = 0;
};

#endif // ICALCULATOR_H
