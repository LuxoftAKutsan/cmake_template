#ifndef BAR_MOCK_H
#define BAR_MOCK_H

#include "gmock/gmock.h"
#include "ibar.hpp"

class BarMock : public IBar
{
public:
    MOCK_CONST_METHOD0(available, bool());
};

#endif // BAR_MOCK_H
