//
// Created by robcholz on 2/19/24.
//
#include "anemos/ast/IfExpressionAST.hpp"

using namespace anemos;

IfExpressionAST::IfExpressionAST(std::unique_ptr<ExpressionAST> condition,
                                 std::unique_ptr<ExpressionAST> thenBranch,
                                 std::unique_ptr<ExpressionAST> elseBranch) {
  this->exprCondition = std::move(condition);
  this->exprThenBranch = std::move(thenBranch);
  this->exprElseBranch = std::move(elseBranch);
}

void IfExpressionAST::execute() {}