#ifndef NCONSTANTS_HPP
#define NCONSTANTS_HPP

#include <functional>
#include <string>

namespace NHelper
{
    template<typename T>
    using TBinaryFunction = ::std::function<T(const T&, const T&)>;

    const char plusSign           = '+';
    const char minusSign          = '-';
    const char multiplicationSign = '*';
    const char divisionSign       = '/';
    const char dotCharacter       = '.';
    const char argumentDelimeter  = ' ';

    bool parseNumber(const ::std::string& str, double& outResult);

    template<typename T>
    void clearCollection(T& collection)
    {
        T().swap(collection);
    }
}

#endif // NCONSTANTS_HPP
