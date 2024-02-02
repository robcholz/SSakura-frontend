//
// Created by robcholz on 11/25/23.
//
#include "ast/NumberExprAST.hpp"

using namespace ssa;

NumberExprAST::NumberExprAST(ssa::s_i64_t i64) {
  Primitive type= getMinBits(i64);
  this->constant=std::make_unique<VariableConstant>(Type{type},Value{i64});
}

NumberExprAST::NumberExprAST(ssa::s_u64_t u64) {
  Primitive type= getMinBits(u64);
  this->constant=std::make_unique<VariableConstant>(Type{type},Value{u64});
}

NumberExprAST::NumberExprAST(ssa::s_f64_t f64) {
  Primitive type = getMinBits(f64);
  this->constant = std::make_unique<VariableConstant>(Type{type}, Value{f64});
}

Value NumberExprAST::codeGen() {}
