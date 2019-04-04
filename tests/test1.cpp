#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cmath>

#include "calculator.h"

TEST(cacluator, check_illegal_input) {
  const std::string illegal_input_1("/");
  const std::string illegal_input_2("1 2 3");
  const std::string illegal_input_3("1 2 + +");
  const std::string illegal_input_4("1 2 + 3 4");

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(illegal_input_1, result), ErrorCodes::kIllegalInput);
  EXPECT_EQ(calculator.Calculate(illegal_input_2, result), ErrorCodes::kIllegalInput);
  EXPECT_EQ(calculator.Calculate(illegal_input_3, result), ErrorCodes::kIllegalInput);
  EXPECT_EQ(calculator.Calculate(illegal_input_4, result), ErrorCodes::kIllegalInput);
}

TEST(cacluator, check_ending_equal_sign) {
  const std::string illegal_input("1 2 +");
  const std::string legal_input("1 2 + =");

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(illegal_input, result), ErrorCodes::kIllegalInput);
  EXPECT_EQ(calculator.Calculate(legal_input, result), ErrorCodes::kOk);
}

TEST(cacluator, check_max_values) {
  const std::string illegal_input("2e308 2e308 +");

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(illegal_input, result), ErrorCodes::kOverflow);
}

TEST(cacluator, check_computation_overflow) {
  const std::string illegal_input("1.1e308 1.1e308 + =");

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(illegal_input, result), ErrorCodes::kOverflow);
}

TEST(cacluator, check_illegal_operations) {
  const std::string illegal_input("0 0 / =");

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(illegal_input, result), ErrorCodes::kIllegalOperation);
}

TEST(cacluator, check_adding) {
  const std::string input_1("1 1 + =");
  const double result_1 = 2;
  const std::string input_2("1 -3 + =");
  const double result_2 = -2;
  const std::string input_3("1.5 1 + =");
  const double result_3 = 2.5;
  const std::string input_4("0.5 1.5 + =");
  const double result_4 = 2;

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(input_1, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_1);

  EXPECT_EQ(calculator.Calculate(input_2, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_2);

  EXPECT_EQ(calculator.Calculate(input_3, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_3);

  EXPECT_EQ(calculator.Calculate(input_4, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_4);
}

TEST(cacluator, check_multiplication) {
  const std::string input_1("1 1 * =");
  const double result_1 = 1;
  const std::string input_2("1 -3 * =");
  const double result_2 = -3;

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(input_1, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_1);

  EXPECT_EQ(calculator.Calculate(input_2, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_2);
}

TEST(cacluator, check_division) {
  const std::string input_1("1 1 / =");
  const double result_1 = 1;
  const std::string input_2("6 -3 / =");
  const double result_2 = -2;

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(input_1, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_1);

  EXPECT_EQ(calculator.Calculate(input_2, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_2);
}

TEST(cacluator, complex_operations) {
  const std::string input_1("1 1 / 2 + =");
  const double result_1 = 3;
  const std::string input_2("6 -3 * 2 + =");
  const double result_2 = -16;

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(input_1, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_1);

  EXPECT_EQ(calculator.Calculate(input_2, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_2);
}

TEST(cacluator, wikipedia_example) {
  const std::string input_1("15 7 1 1 + - / 3 * 2 1 1 + + - =");
  const double result_1 = 5;

  Calculator calculator;
  double result;
  EXPECT_EQ(calculator.Calculate(input_1, result), ErrorCodes::kOk);
  EXPECT_DOUBLE_EQ(result, result_1);
}
