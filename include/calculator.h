#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "icalculator.h"

class Calculator : public ICalculator {
public:
    Calculator();

    ErrorCodes Calculate(const std::string& input, double& result) override;
};

#endif // CALCULATOR_H
