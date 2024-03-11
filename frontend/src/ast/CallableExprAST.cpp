//
// Created by robcholz on 11/25/23.
//
#include "ssa/ast/CallableExprAST.hpp"
#include "ssa/Info.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

CallableExprAST::CallableExprAST(std::string callable,
                                 std::unique_ptr<ActualParameter> parameter) {
  this->callable = std::move(callable);
  this->parameter = std::move(parameter);
}

Value CallableExprAST::codeGen() {
  return {Primitive::I8};
  //return ASTAdapter::callableExprGen(callable, *arguments);
}

ExprAST::ExprType CallableExprAST::getType() const {
  return ExprAST::ExprType::CALLABLE_EXPR;
}

/*
std::expected<ssa::Type, ExprAST::ExprType> CallableExprAST::hasReturnType()
    const {
  // TODO
  // 1. set up the callable registry
  // 2. setup the recursive auto deduce return type
  //return callable->hasReturnType();
  return std::unexpected(ExprAST::ExprType::CALLABLE_EXPR);
}
*/

const std::string& CallableExprAST::getName() const {
  return callable;
}

const ActualParameter& CallableExprAST::getParameter() const {
  return *parameter;
}
