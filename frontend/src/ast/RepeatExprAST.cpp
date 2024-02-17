//
// Created by robcholz on 11/28/23.
//
#include "ast/RepeatExprAST.hpp"
#include "Info.hpp"

using namespace ssa;

RepeatExprAST::RepeatExprAST(const Type repeatType,
                             std::unique_ptr<ExprAST> conditionExpr,
                             std::unique_ptr<ExprAST> bodyExpr) {
  this->repeatType = repeatType;
  this->conditionExpr = std::move(conditionExpr);
  this->bodyExpr = std::move(bodyExpr);
}

Value RepeatExprAST::codeGen() {}  // REPEAT_UNTIL
