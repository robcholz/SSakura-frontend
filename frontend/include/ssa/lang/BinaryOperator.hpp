//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BINARYOPERATOR_HPP
#define SSAKURA_FRONTEND_BINARYOPERATOR_HPP

#include "ssa/Token.hpp"

namespace ssa {
class BinaryOperator {
 public:
  enum BinaryOperatorEnum : int {
    ADD,
    SUBTRACT,
    MULTIPLE,
    DIVISION,
    MOD,
    GREATER,
    LESS,

    EQUAL,
    NOT,
    AND,
    OR,
  };

  static BinaryOperatorEnum getOperator(const Token& token);
  static int getPrecedence(const Token& token);
  static int getPrecedence(BinaryOperator::BinaryOperatorEnum binaryOperator);
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_BINARYOPERATOR_HPP
