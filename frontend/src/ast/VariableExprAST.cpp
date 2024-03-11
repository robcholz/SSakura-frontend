//
// Created by robcholz on 11/25/23.
//
#include "ssa/ast/VariableExprAST.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

VariableExprAST::VariableExprAST(const std::string& name) : name(name) {}

Value VariableExprAST::codeGen() {
  return ASTAdapter::variableExprGen(name);
}

std::string VariableExprAST::getName() const {
  return name;
}

ExprAST::ExprType VariableExprAST::getType() const {
  return ExprAST::ExprType::VARIABLE_EXPR;
}
