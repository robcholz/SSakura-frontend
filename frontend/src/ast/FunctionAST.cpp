//
// Created by robcholz on 11/26/23.
//
#include "ast/FunctionAST.hpp"
#include "Info.hpp"
#include "adapter/ASTAdapter.hpp"
#include "ast/ExprAST.hpp"
#include "ast/ProtoTypeAST.hpp"

using namespace ssa;

FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                         std::unique_ptr<ExprAST> body) {
  this->prototype = std::move(prototype);
  this->body = std::move(body);
}

Value FunctionAST::codeGen() {
  return ASTAdapter::functionExprGen(prototype, body);
}
