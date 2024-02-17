//
// Created by robcholz on 2/17/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ARITHMETICOPERATIONADAPTER_HPP
#define SSAKURA_FRONTEND_ARITHMETICOPERATIONADAPTER_HPP

#include "ast/BinaryExprAST.hpp"

namespace ssa {
class ArithmeticOperationAdapter {
 public:
  ArithmeticOperationAdapter() = delete;
  ~ArithmeticOperationAdapter() = delete;
  ArithmeticOperationAdapter& operator=(ArithmeticOperationAdapter&) = delete;

  static Value equalityGen(const Value& left, const Value& right) {return Value{1};}
  static Value greaterThanGen(const Value& left, const Value& right) {return Value{1};}
  static Value lessThanGen(const Value& left, const Value& right) {return Value{1};}
  static Value boolAndGen(const Value& left, const Value& right) {return Value{1};}
  static Value boolOrGen(const Value& left, const Value& right) {return Value{1};}
  static Value boolNotGen(const Value& value) {return Value{1};}
  static Value modulusGen(const Value& left, const Value& right) {return Value{1};}
  static Value addGen(const Value& left, const Value& right) {return Value{1};}
  static Value subtractGen(const Value& left, const Value& right) {return Value{1};}
  static Value multipleGen(const Value& left, const Value& right) {return Value{1};}
  static Value divisionGen(const Value& left, const Value& right) {return Value{1};}
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_ARITHMETICOPERATIONADAPTER_HPP
