//
// Created by robcholz on 11/28/23.
//
#include "ast/IfExprAST.hpp"
#include "Info.hpp"
#include "type/Type.hpp"
#include "adapter/ASTAdapter.hpp"

using namespace ssa;

IfExprAST::IfExprAST(std::unique_ptr<ExprAST> condition,
                     std::unique_ptr<ExprAST> thenExpr,
                     std::unique_ptr<ExprAST> elseExpr) {
  this->condition = std::move(condition);
  this->thenExpr = std::move(thenExpr);
  this->elseExpr = std::move(elseExpr);
}

Value IfExprAST::codeGen() {
  return ASTAdapter::ifExprGen(condition,thenExpr,elseExpr);
}
