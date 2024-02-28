//
// Created by robcholz on 11/25/23.
//
#include "ssa/ast/CallableExprAST.hpp"
#include "ssa/Info.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

CallableExprAST::CallableExprAST(
    const std::string& callable,
    std::vector<std::unique_ptr<ExprAST>> arguments) {
  this->callable = callable;
  this->arguments = std::move(arguments);
}

Value CallableExprAST::codeGen() {
  return ASTAdapter::callableExprGen(callable, arguments);
}

ExprAST::Type CallableExprAST::getType() const {
  return ExprAST::Type::CALLABLE_EXPR;
}
