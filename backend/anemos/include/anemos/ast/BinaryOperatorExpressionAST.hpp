//
// Created by robcholz on 2/27/24.
//
#pragma once

#ifndef ANEMOS_BINARYOPERATOREXPRESSIONAST_HPP
#define ANEMOS_BINARYOPERATOREXPRESSIONAST_HPP

#include <memory>
#include "ExpressionAST.hpp"

namespace anemos {
class BinaryOperatorExpressionAST : public ExpressionAST {
 public:
  enum BinaryOperatorEnum {
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

  explicit BinaryOperatorExpressionAST(BinaryOperatorEnum binaryOperator,
                                       std::unique_ptr<ExpressionAST> lhs,
                                       std::unique_ptr<ExpressionAST> rhs);

  void execute() override;

 private:
  BinaryOperatorEnum binaryOperatorEnum;

  std::unique_ptr<ExpressionAST> leftExpression;
  std::unique_ptr<ExpressionAST> rightExpression;
};
}  // namespace anemos

#endif  // ANEMOS_BINARYOPERATOREXPRESSIONAST_HPP
