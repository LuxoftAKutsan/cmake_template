#ifndef ICALCULATOR_H
#define ICALCULATOR_H

#include <string>

#include "types.h"

class ICalculator {
public:
  virtual ErrorCodes Calculate(const std::string& input, double& result) = 0;
};

#endif // ICALCULATOR_H
