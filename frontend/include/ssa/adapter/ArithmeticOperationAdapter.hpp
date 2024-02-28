//
// Created by robcholz on 2/17/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ARITHMETICOPERATIONADAPTER_HPP
#define SSAKURA_FRONTEND_ARITHMETICOPERATIONADAPTER_HPP

#include <functional>
#include "ssa/Attribute.hpp"
#include "ssa/ast/BinaryExprAST.hpp"

namespace ssa {
class AdapterRegistry;
class ArithmeticOperationAdapter {
 public:
  ArithmeticOperationAdapter() = delete;
  ~ArithmeticOperationAdapter() = delete;
  ArithmeticOperationAdapter& operator=(ArithmeticOperationAdapter&) = delete;

  static SSA_FORCE_INLINE Value equalityGen(const Value& left,
                                            const Value& right);
  static SSA_FORCE_INLINE Value greaterThanGen(const Value& left,
                                               const Value& right);
  static SSA_FORCE_INLINE Value lessThanGen(const Value& left,
                                            const Value& right);
  static SSA_FORCE_INLINE Value boolAndGen(const Value& left,
                                           const Value& right);
  static SSA_FORCE_INLINE Value boolOrGen(const Value& left,
                                          const Value& right);
  static SSA_FORCE_INLINE Value boolNotGen(const Value& value);
  static SSA_FORCE_INLINE Value modulusGen(const Value& left,
                                           const Value& right);
  static SSA_FORCE_INLINE Value addGen(const Value& left, const Value& right);
  static SSA_FORCE_INLINE Value subtractGen(const Value& left,
                                            const Value& right);
  static SSA_FORCE_INLINE Value multipleGen(const Value& left,
                                            const Value& right);
  static SSA_FORCE_INLINE Value divisionGen(const Value& left,
                                            const Value& right);

 private:
  friend AdapterRegistry;

  static inline std::function<Value(const Value&, const Value&)>
      equalityCallback;
  static inline std::function<Value(const Value&, const Value&)>
      greaterThanCallback;
  static inline std::function<Value(const Value&, const Value&)>
      lessThanCallback;
  static inline std::function<Value(const Value&, const Value&)>
      boolAndCallback;
  static inline std::function<Value(const Value&, const Value&)> boolOrCallback;
  static inline std::function<Value(const Value&)> boolNotCallback;
  static inline std::function<Value(const Value&, const Value&)>
      modulusCallback;
  static inline std::function<Value(const Value&, const Value&)> addCallback;
  static inline std::function<Value(const Value&, const Value&)>
      subtractCallback;
  static inline std::function<Value(const Value&, const Value&)>
      multipleCallback;
  static inline std::function<Value(const Value&, const Value&)>
      divisionCallback;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_ARITHMETICOPERATIONADAPTER_HPP
