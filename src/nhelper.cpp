#include "nhelper.hpp"

namespace NHelper {

    bool parseNumber(const std::string &str, double &outResult)
    {
        bool isParsingSuccessfull = false;
        if(false == str.empty())
        {
            char* tmp = nullptr;

            outResult = ::std::strtod(str.c_str(), &tmp);

            isParsingSuccessfull = (tmp == str.c_str() + str.size());
        }

        return isParsingSuccessfull;
    }
}
