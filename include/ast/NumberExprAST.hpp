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
  explicit NumberExprAST(s_i64_t i64);
  /// the constructor will choose the smallest unsigned type to hold the value
  explicit NumberExprAST(s_u64_t u64);
  // the constructor will choose the smallest floating type to hold the value
  explicit NumberExprAST(s_f64_t f64);


  Value codeGen() final;

 private:
  std::unique_ptr<VariableConstant> constant;
};
}  // namespace ssa

#endif  // SSAKURA_NUMBEREXPRAST_HPP
