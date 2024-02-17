//
// Created by robcholz on 1/31/24.
//
#include "value/Value.hpp"

using namespace ssa;

Value::Value(const Value::VariantT& value) : type({}) {
  initializeFrom(value);
}

Value::Value(const Type& type,
             const Value::VariantT& value)
    : type(type), primitiveValue(value) {}

Value& Value::operator=(const Value::VariantT& value) {
  initializeFrom(value);
  return *this;
}

const Type& Value::getType() const {
  return type;
}
