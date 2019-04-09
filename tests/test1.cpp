#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "foo_mock.hpp"
#include "bar_mock.h"

using ::testing::Return;

int func_to_test(IFoo& foo, IBar& bar)
{
    int ret = 0;

    if(true == bar.available()){
        bool x = foo.doStuff();
        ret = (x ? 100 : 50);
    }

    return ret;
}

/*TEST(example, foo_mock_return_false)
{
    FooMock fooMock;
    ::testing::NiceMock<BarMock> barMock;

    //Arrange
    ON_CALL(barMock, available()).WillByDefault(Return(true));

    //Assert
    EXPECT_CALL(fooMock, doStuff()).Times(1).WillOnce(Return(false));

    //Act
    int res = func_to_test(fooMock, barMock);

    //Check
    EXPECT_EQ(res, 50);
}

TEST(example, available_is_false)
{
    FooMock fooMock;
    ::testing::NiceMock<BarMock> barMock;

    //Arrange
    ON_CALL(barMock, available()).WillByDefault(Return(false));

    //Assert
    ON_CALL(fooMock, doStuff()).WillByDefault(Return(false));

    //Act
    int res = func_to_test(fooMock, barMock);

    //Check
    EXPECT_EQ(res, 0);
}

TEST(example, foo_mock_return_true)
{
    FooMock fooMock;
    ::testing::NiceMock<BarMock> barMock;

    //Arrange
    ON_CALL(barMock, available()).WillByDefault(Return(true));

    //Assert
    EXPECT_CALL(fooMock, doStuff()).Times(1).WillOnce(Return(true));

    //Act
    int res = func_to_test(fooMock, barMock);

    //Check
    EXPECT_EQ(res, 100);
}

TEST(example, available_is_false_call)
{
    FooMock fooMock;
    ::testing::NiceMock<BarMock> barMock;

    //Arrange
    ON_CALL(barMock, available()).WillByDefault(Return(false));

    //Assert
    ON_CALL(fooMock, doStuff()).WillByDefault(Return(true));

    //Act
    func_to_test(fooMock, barMock);
}*/
