//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_NUMBEREXPRAST_HPP
#define SSAKURA_NUMBEREXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"
#include "rule/VariableConstant.hpp"

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

  Value codeGen() final;

 private:
  std::unique_ptr<VariableConstant> constant;
};
}  // namespace ssa

#endif  // SSAKURA_NUMBEREXPRAST_HPP
