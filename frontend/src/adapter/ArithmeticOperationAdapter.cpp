//
// Created by robcholz on 2/18/24.
//
#include "adapter/ArithmeticOperationAdapter.hpp"

using namespace ssa;

Value ArithmeticOperationAdapter::equalityGen(const ssa::Value& left,
                                              const ssa::Value& right) {
  return equalityCallback(left, right);
}

Value ArithmeticOperationAdapter::greaterThanGen(const ssa::Value& left,
                                                 const ssa::Value& right) {
  return greaterThanCallback(left, right);
}

Value ArithmeticOperationAdapter::lessThanGen(const ssa::Value& left,
                                              const ssa::Value& right) {
  return lessThanCallback(left, right);
}

Value ArithmeticOperationAdapter::boolAndGen(const ssa::Value& left,
                                             const ssa::Value& right) {
  return boolAndCallback(left, right);
}

Value ArithmeticOperationAdapter::boolOrGen(const ssa::Value& left,
                                            const ssa::Value& right) {
  return boolOrCallback(left, right);
}

Value ArithmeticOperationAdapter::boolNotGen(const ssa::Value& value) {
  return boolNotCallback(value);
}

Value ArithmeticOperationAdapter::modulusGen(const ssa::Value& left,
                                             const ssa::Value& right) {
  return modulusCallback(left, right);
}

Value ArithmeticOperationAdapter::addGen(const ssa::Value& left,
                                         const ssa::Value& right) {
  return addCallback(left, right);
}

Value ArithmeticOperationAdapter::subtractGen(const ssa::Value& left,
                                              const ssa::Value& right) {
  return subtractCallback(left, right);
}

Value ArithmeticOperationAdapter::multipleGen(const ssa::Value& left,
                                              const ssa::Value& right) {
  return multipleCallback(left, right);
}

Value ArithmeticOperationAdapter::divisionGen(const ssa::Value& left,
                                              const ssa::Value& right) {
  return divisionCallback(left, right);
}
