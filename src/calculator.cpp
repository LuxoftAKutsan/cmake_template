#include <algorithm>
#include <sstream>
#include <string>
#include <iterator>
#include <map>

#include "calculator.hpp"

double Calculator::calculate(const std::string &argument)
{
    clearBuffers();
    parseArgument(argument);

    return performCalculation();
}

void Calculator::parseArgument(const std::string &argument)
{
    bool isOperatorsPart = false;
    auto params = splitArgument(argument);

    for(const ::std::string& currentSubString : params)
    {
        double currentNumber = 0;
        bool   isNumber      = NHelper::parseNumber(currentSubString, currentNumber);

        if(true == isNumber && false == isOperatorsPart)
        {
            mNumbers.push(currentNumber);
        }
        else if(true == isNumber && true == isOperatorsPart)
        {
            throw ::std::invalid_argument("Argument parse error");
        }
        else
        {
            isOperatorsPart = true;
            parseOperations(currentSubString);
        }
    }

    bool isCountMatch =  mOperators.size() == (mNumbers.size() - 1);
    if(false == isCountMatch)
    {
        throw ::std::invalid_argument("Count of numbers does not match to count of operators!");
    }
}

void Calculator::parseOperations(const ::std::string &operation)
{
    static ::std::map<char, NHelper::TBinaryFunction<double>> operations
    {
        { NHelper::plusSign,           ::std::plus<double>()       },
        { NHelper::minusSign,          ::std::minus<double>()      },
        { NHelper::multiplicationSign, ::std::multiplies<double>() },
        { NHelper::divisionSign,       ::std::divides<double>()    }
    };

    if(operation.size() == 1)
    {
        auto it = operations.find(operation.front());

        if(operations.end() != it)
        {
           mOperators.push(it->second);
        }
        else
        {
           throw ::std::invalid_argument("Unrecognised operator!");
        }
    }
    else
    {
        throw ::std::invalid_argument("Unrecognised operator!");
    }
}

::std::vector<std::string> Calculator::splitArgument(const std::string &argument)
{
    ::std::istringstream iss(argument);

    ::std::vector<std::string> result((::std::istream_iterator<::std::string>(iss)),
                                      (::std::istream_iterator<::std::string>()));

    return result;
}

double Calculator::performCalculation()
{
    while(false == mOperators.empty())
    {
        auto currentOperation = mOperators.front();
        mOperators.pop();

        double second = mNumbers.top();
        mNumbers.pop();
        double first = mNumbers.top();
        mNumbers.pop();

        double result = currentOperation(first, second);

        if(::std::numeric_limits<double>::infinity() == result)
        {
            throw ::std::out_of_range("Division by zero!");
        }

        mNumbers.push(result);
    }

    return mNumbers.top();
}

void Calculator::clearBuffers()
{
    NHelper::clearCollection(mNumbers);
    NHelper::clearCollection(mOperators);
}
