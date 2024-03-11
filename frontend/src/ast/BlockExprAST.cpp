//
// Created by robcholz on 2/2/24.
//
#include "ssa/ast/BlockExprAST.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

BlockExprAST::BlockExprAST(std::unique_ptr<ExprAST> expr) {
  add(std::move(expr));
}

void BlockExprAST::add(std::unique_ptr<ExprAST> expr) {
  blockExpr.push_back(std::move(expr));
}

Value BlockExprAST::codeGen() {
  return ASTAdapter::blockExprGen();
}

ExprAST::ExprType BlockExprAST::getType() const {
  return ExprAST::ExprType::BLOCK_EXPR;
}
