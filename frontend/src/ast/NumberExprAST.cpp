//
// Created by robcholz on 11/25/23.
//
#include "ast/NumberExprAST.hpp"

using namespace ssa;

NumberExprAST::NumberExprAST(
    primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE> number) {
  Primitive type = getMinBits(number);
  this->constant =
      std::make_unique<VariableConstant>(Type{type}, Value{number});
}

NumberExprAST::NumberExprAST(
    primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE> number) {
  Primitive type = getMinBits(number);
  this->constant =
      std::make_unique<VariableConstant>(Type{type}, Value{number});
}

NumberExprAST::NumberExprAST(
    primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE> number) {
  Primitive type = getMinBits(number);
  this->constant =
      std::make_unique<VariableConstant>(Type{type}, Value{number});
}

Value NumberExprAST::codeGen() {}
