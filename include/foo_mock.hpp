#ifndef FOO_MOCK_HPP
#define FOO_MOCK_HPP

#include "gmock/gmock.h"
#include "ifoo.h"

class FooMock : public IFoo {
public:
    MOCK_METHOD0(doStuff, bool());
};

#endif // FOO_MOCK_HPP
