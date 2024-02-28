//
// Created by robcholz on 2/27/24.
//
#include "anemos/ast/BinaryOperatorExpressionAST.hpp"

using namespace anemos;

BinaryOperatorExpressionAST::BinaryOperatorExpressionAST(
    BinaryOperatorExpressionAST::BinaryOperatorEnum binaryOperator,
    std::unique_ptr<ExpressionAST> lhs,
    std::unique_ptr<ExpressionAST> rhs) {
  this->binaryOperatorEnum = binaryOperator;
  this->leftExpression = std::move(lhs);
  this->rightExpression = std::move(rhs);
}

void BinaryOperatorExpressionAST::execute() {}
