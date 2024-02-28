//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_NUMBEREXPRAST_HPP
#define SSAKURA_NUMBEREXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"
#include "ssa/rule/VariableConstant.hpp"

namespace ssa {
class NumberExprAST : public ExprAST {
 public:
  /// the constructor will choose the smallest signed type to hold the value
  explicit NumberExprAST(primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE> number);
  /// the constructor will choose the smallest unsigned type to hold the value
  explicit NumberExprAST(
      primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE> number);
  // the constructor will choose the smallest floating type to hold the value
  explicit NumberExprAST(primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE> number);

  const Value& getNumber() const;

  Value codeGen() final;
  ExprAST::Type getType() const final;

 private:
  std::unique_ptr<Value> constant;
};
}  // namespace ssa

#endif  // SSAKURA_NUMBEREXPRAST_HPP
