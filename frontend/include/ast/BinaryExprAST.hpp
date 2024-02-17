//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BINARYEXPRAST_HPP
#define SSAKURA_FRONTEND_BINARYEXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"
#include "lang/BinaryOperator.hpp"

namespace ssa {
class BinaryExprAST : public ExprAST {
 public:
  explicit BinaryExprAST(BinaryOperator::BinaryOperatorEnum op,
                         std::unique_ptr<ExprAST> leftExprAst,
                         std::unique_ptr<ExprAST> rightExprAst);
  Value codeGen() final;

 private:
  BinaryOperator::BinaryOperatorEnum op;
  std::unique_ptr<ExprAST> leftExprAst;
  std::unique_ptr<ExprAST> rightExprAst;


  static Value equality(const Value& left, const Value& right);
  static Value greaterThan(const Value& left, const Value& right);
  static Value lessThan(const Value& left, const Value& right);
  static Value boolAnd(const Value& left, const Value& right);
  static Value boolOr(const Value& left, const Value& right);
  static Value boolNot(const Value& value);
  static Value modulus(const Value& left, const Value& right);
  static Value add(const Value& left, const Value& right);
  static Value subtract(const Value& left, const Value& right);
  static Value multiple(const Value& left, const Value& right);
  static Value division(const Value& left, const Value& right);
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_BINARYEXPRAST_HPP
