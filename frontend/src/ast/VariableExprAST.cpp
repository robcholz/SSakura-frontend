//
// Created by robcholz on 11/25/23.
//
#include "ast/VariableExprAST.hpp"

using namespace ssa;

VariableExprAST::VariableExprAST(const std::string& name) : name(name) {}

Value VariableExprAST::codeGen() {

}
