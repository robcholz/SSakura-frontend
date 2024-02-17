//
// Created by robcholz on 11/25/23.
//
#include "ast/VariableExprAST.hpp"
#include "adapter/ASTAdapter.hpp"

using namespace ssa;

VariableExprAST::VariableExprAST(const std::string& name) : name(name) {}

Value VariableExprAST::codeGen() {
  return ASTAdapter::variableExprGen(name);
}
