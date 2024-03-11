//
// Created by robcholz on 11/26/23.
//
#include "ssa/ast/FunctionAST.hpp"
#include "ssa/Info.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                         std::unique_ptr<BlockExprAST> body) {
  this->prototype = std::move(prototype);
  this->body = std::move(body);
}

FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                         std::unique_ptr<ExprAST> body) {
  this->prototype = std::move(prototype);
  this->body = std::make_unique<BlockExprAST>(std::move(body));
}

const PrototypeAST& FunctionAST::getPrototype() const {
  return *prototype;
}

const BlockExprAST& FunctionAST::getBody() const {
  return *body;
}

Value FunctionAST::codeGen() {
  return ASTAdapter::functionExprGen(prototype, body);
}

ExprAST::ExprType FunctionAST::getType() const {
  return ExprAST::ExprType::FUNCTION_EXPR;
}

std::expected<ssa::Type, ExprAST::ExprType> FunctionAST::hasReturnType() const {
  return prototype->getReturnType();
}
