//
// Created by robcholz on 2/2/24.
//
#include "ast/BlockExprAST.hpp"
#include "adapter/ASTAdapter.hpp"

using namespace ssa;

Value BlockExprAST::codeGen() {
  return ASTAdapter::blockExprGen();
}