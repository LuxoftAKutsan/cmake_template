#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "calculator.hpp"

TEST(parsing, valid_input_received)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("45 40 -");

    EXPECT_DOUBLE_EQ(result, 5);
}

TEST(parsing, invalid_number_received)
{
    Calculator calcualtor;

    EXPECT_THROW(calcualtor.calculate("4a 40 -"), ::std::invalid_argument);
}

TEST(parsing, invalid_operator_received)
{
    Calculator calcualtor;

    EXPECT_THROW(calcualtor.calculate("10 40 d"), ::std::invalid_argument);
}

TEST(parsing, operands_count_mismatch)
{
    Calculator calcualtor;

    EXPECT_THROW(calcualtor.calculate("10 5 4 -"), ::std::invalid_argument);
}

TEST(single_operation, adding)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("45 40 +");

    EXPECT_DOUBLE_EQ(result, 85);
}

TEST(single_operation, substraction)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("5 8 -");

    EXPECT_DOUBLE_EQ(result, -3);
}

TEST(single_operation, multiplication)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("5 8 *");

    EXPECT_DOUBLE_EQ(result, 40);
}

TEST(single_operation, division)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("21 3 /");

    EXPECT_DOUBLE_EQ(result, 7);
}

TEST(single_operation, division_by_zero)
{
    Calculator calcualtor;

    EXPECT_THROW(calcualtor.calculate("5 0 /"), ::std::out_of_range);
}

TEST(number_sign, positive_number)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("21 3 -");

    EXPECT_DOUBLE_EQ(result, 18);
}

TEST(number_sign, negative_number)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("-21 -3 /");

    EXPECT_DOUBLE_EQ(result, 7);
}

TEST(multiple_operations, calculate)
{
    Calculator calcualtor;

    double result = calcualtor.calculate("-21 -3 5 -2 / * +");

    EXPECT_DOUBLE_EQ(result, -13.5);
}
