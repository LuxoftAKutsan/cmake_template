#include "calculator.h"

#include <cmath>
#include <stdexcept>
#include <vector>
#include <stack>
#include <map>
#include <assert.h>

//////////////////////////////////////////////////////////////////////
/// Constants
//////////////////////////////////////////////////////////////////////

const std::string kAdditionOperator("+");
const std::string kSubstitutionOperator("-");
const std::string kMultiplicationOperator("*");
const std::string kDivisionOperator("/");
const std::string kEqualityOperator("=");

//////////////////////////////////////////////////////////////////////
/// Enumerations
//////////////////////////////////////////////////////////////////////

enum class ElementTypes {
  kUnknonwn,
  kNumber,
  kOutOfRangeNumber,
  kOperator
};

enum class OperatorTypes {
  kAddition,
  kSubstution,
  kMultiplication,
  kDivision,
  kEquality
};

//////////////////////////////////////////////////////////////////////
/// Helper functions
//////////////////////////////////////////////////////////////////////

/**
 * @brief split
 * @param txt
 * @param strs
 * @param ch
 * @return
 */
size_t split(const std::string &txt, std::vector<std::string> &strs_out, char ch)
{
  size_t pos = txt.find( ch );
  size_t initialPos = 0;
  strs_out.clear();

  // Decompose statement
  while( pos != std::string::npos ) {
    const auto next_element_length = pos - initialPos;
    const auto next_element = txt.substr( initialPos,  next_element_length);
    strs_out.emplace_back(next_element);
    initialPos = pos + 1;

    pos = txt.find( ch, initialPos );
  }

  // Add the last one
  const auto last_element_length = txt.size() - initialPos + 1 ;
  const auto last_element = txt.substr( initialPos,last_element_length ) ;
  strs_out.push_back(last_element);

  return strs_out.size();
}

/**
 * @brief GetOperatorType
 * Requires validated input parameter.
 * In case if inputparameter is not valid, funciton will asser in debug .
 * Release behaviour is undefined
 * @param element
 * @return
 */
OperatorTypes GetOperatorType(const std::string& element) {
  static const std::map<std::string,OperatorTypes> operators =
  {
    {kAdditionOperator,OperatorTypes::kAddition},
    {kSubstitutionOperator,OperatorTypes::kSubstution},
    {kMultiplicationOperator,OperatorTypes::kMultiplication},
    {kDivisionOperator,OperatorTypes::kDivision},
    {kEqualityOperator,OperatorTypes::kEquality}
  };
  auto it = operators.find(element);
  assert(it != operators.end());
  return it->second;
}


ElementTypes GetElementType(const std::string& element) {

  auto is_operator = [&element] () {
    return  kAdditionOperator == element ||
        kAdditionOperator == element ||
        kSubstitutionOperator == element ||
        kMultiplicationOperator == element ||
        kDivisionOperator == element ||
        kEqualityOperator == element;
  };

  if (is_operator()) {
    return ElementTypes::kOperator;
  }

  try {
    std::stod(element);
    return ElementTypes::kNumber;
  } catch(const std::out_of_range& out_of_range) {
    return ElementTypes::kOutOfRangeNumber;
  }
  return ElementTypes::kUnknonwn;
}


/**
 * @brief IdentifyElement
 * @param element
 * @param number
 * @param operator_type
 * @return
 */
void GetElementAndOperatorType(const std::string& element,
                               OperatorTypes& operator_type_out,
                               ElementTypes& elemet_type_out) {

}

ElementTypes IdentifyElement(const std::string& element,
                             double& number_out,
                             OperatorTypes& operator_type_out) {

  const ElementTypes elemet_type = GetElementType(element);

  if (ElementTypes::kOperator == elemet_type ) {
    operator_type_out = GetOperatorType(element);
  }

  if (ElementTypes::kNumber == elemet_type) {
    number_out = std::stod(element);
  }

  return elemet_type;
}

ErrorCodes ExecuteOperator(OperatorTypes operator_type, double left_operand, double right_operand, double& result) {
  ErrorCodes error_code = ErrorCodes::kOk;

  switch(operator_type) {
  case OperatorTypes::kAddition:
    result = left_operand + right_operand;
    break;
  case OperatorTypes::kSubstution:
    result = left_operand - right_operand;
    break;
  case OperatorTypes::kMultiplication:
    result = left_operand * right_operand;
    break;
  case OperatorTypes::kDivision:
    if  (0 == right_operand) {
      error_code = ErrorCodes::kIllegalOperation;
    } else {
      result = left_operand / right_operand;
    }
    break;
  }

  return error_code;
}

//////////////////////////////////////////////////////////////////////
/// Class members
//////////////////////////////////////////////////////////////////////

Calculator::Calculator() {

}

ErrorCodes Calculator::Calculate(const std::string& input, double& result) {
  ErrorCodes error_code = ErrorCodes::kOk;

  std::vector<std::string> input_parameters;
  split(input, input_parameters, ' ');
  std::stack<double> numbers_vault;
  for (std::size_t i = 0; i < input_parameters.size(); ++i) {
    double elment_number;
    OperatorTypes operator_type;
    ElementTypes element_type = IdentifyElement(input_parameters[i], elment_number, operator_type);
    // Check error conditions.
    if (ElementTypes::kUnknonwn == element_type) {
      error_code = ErrorCodes::kIllegalInput;
      break;
    }
    if (ElementTypes::kOutOfRangeNumber == element_type) {
      error_code = ErrorCodes::kOverflow;
      break;
    }
    if ((input_parameters.size() - 1) == i) {
      if ((ElementTypes::kOperator != element_type) || (OperatorTypes::kEquality != operator_type)) {
        error_code = ErrorCodes::kIllegalInput;
      }
      break;
    } else {
      if ((ElementTypes::kOperator == element_type) && (OperatorTypes::kEquality == operator_type)) {
        error_code = ErrorCodes::kIllegalInput;
        break;
      }
    }

    // Actual computation.
    if (ElementTypes::kNumber == element_type) {
      numbers_vault.push(elment_number);
    } else {
      if (numbers_vault.size() > 1) {
        double operation_result;
        double operand_2 = numbers_vault.top();
        numbers_vault.pop();
        double operand_1 = numbers_vault.top();
        numbers_vault.pop();
        error_code = ExecuteOperator(operator_type, operand_1, operand_2, operation_result);
        if (ErrorCodes::kOk != error_code) {
          break;
        }
        if (!std::isfinite(operation_result)) {
          error_code = ErrorCodes::kOverflow;
          break;
        }
        numbers_vault.push(operation_result);
      } else {
        error_code = ErrorCodes::kIllegalInput;
        break;
      }
    }
  }

  if (ErrorCodes::kOk == error_code) {
    if (numbers_vault.size() == 1) {
      result = numbers_vault.top();
    } else {
      printf("Illegal size of the vault: %u", numbers_vault.size());
    }
  }

  return error_code;
}
