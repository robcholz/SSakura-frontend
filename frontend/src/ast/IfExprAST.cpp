//
// Created by robcholz on 11/28/23.
//
#include "ssa/ast/IfExprAST.hpp"
#include "ssa/Info.hpp"
#include "ssa/adapter/ASTAdapter.hpp"
#include "ssa/type/Type.hpp"

using namespace ssa;

IfExprAST::IfExprAST(std::unique_ptr<ExprAST> condition,
                     std::unique_ptr<ExprAST> thenExpr,
                     std::unique_ptr<ExprAST> elseExpr) {
  this->condition = std::move(condition);
  this->thenExpr = std::move(thenExpr);
  this->elseExpr = std::move(elseExpr);
}

const ExprAST& IfExprAST::getCondition() const {
  return *condition;
}

const ExprAST& IfExprAST::getThenBranch() const {
  return *thenExpr;
}

std::optional<std::reference_wrapper<const ExprAST>> IfExprAST::getElseBranch()
    const {
  if (elseExpr == nullptr)
    return std::nullopt;
  return std::cref(*elseExpr);
}

Value IfExprAST::codeGen() {
  return ASTAdapter::ifExprGen(condition,thenExpr,elseExpr);
}

ExprAST::ExprType IfExprAST::getType() const {
  return ExprAST::ExprType::IF_EXPR;
}
