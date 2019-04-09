#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <exception>
#include <stack>
#include <queue>
#include <functional>

#include "icalculator.hpp"
#include "nhelper.hpp"

class Calculator : ICalculator
{
    public:
        virtual double calculate(const::std::string &argument) override;

    private:

        void parseArgument(const ::std::string& argument);
        void parseOperations(const ::std::string& operation);
        double performCalculation();
        void clearBuffers();

        ::std::vector<::std::string> splitArgument(const ::std::string& argument);

        ::std::stack<double> mNumbers;
        ::std::queue<NHelper::TBinaryFunction<double>> mOperators;
};

#endif // CALCULATOR_HPP
