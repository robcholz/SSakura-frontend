//
// Created by robcholz on 2/27/24.
//
#include "anemos/ast/BlockExpressionAST.hpp"

using namespace anemos;

BlockExpressionAST::BlockExpressionAST(
    std::vector<std::unique_ptr<ExpressionAST>> expressions)
    : exprExpressions(std::move(expressions)) {}

void BlockExpressionAST::execute() {
  for (auto& expr : exprExpressions) {
    expr->execute();
  }
}