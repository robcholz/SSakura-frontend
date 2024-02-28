//
// Created by robcholz on 11/28/23.
//
#include "ssa/ast/RepeatExprAST.hpp"
#include "ssa/Info.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

RepeatExprAST::RepeatExprAST(Type repeatType,
                             std::unique_ptr<ExprAST> conditionExpr,
                             std::unique_ptr<ExprAST> bodyExpr) {
  this->repeatType = repeatType;
  this->conditionExpr = std::move(conditionExpr);
  this->bodyExpr = std::move(bodyExpr);
}

Value RepeatExprAST::codeGen() {
  return ASTAdapter::repeatExprGen(repeatType, conditionExpr, bodyExpr);
}

ExprAST::Type RepeatExprAST::getType() const {
  return ExprAST::Type::REPEAT_EXPR;
}
