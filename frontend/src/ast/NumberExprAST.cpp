//
// Created by robcholz on 11/25/23.
//
#include "ssa/ast/NumberExprAST.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

NumberExprAST::NumberExprAST(
    primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE> number) {
  Primitive type = getMinBits(number);
  this->constant = std::make_unique<Value>(::Type(type), number);
}

NumberExprAST::NumberExprAST(
    primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE> number) {
  Primitive type = getMinBits(number);
  this->constant = std::make_unique<Value>(::Type(type), number);
}

NumberExprAST::NumberExprAST(
    primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE> number) {
  Primitive type = getMinBits(number);
  this->constant = std::make_unique<Value>(::Type(type), number);
}

const Value& NumberExprAST::getNumber() const {
  return *constant;
}

Value NumberExprAST::codeGen() {
  return ASTAdapter::numberExprGen(constant);
}

ExprAST::Type NumberExprAST::getType() const {
  return ExprAST::Type::NUMBER_EXPR;
}
