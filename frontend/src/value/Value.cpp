//
// Created by robcholz on 1/31/24.
//
#include <utility>

#include "ssa/value/Value.hpp"

using namespace ssa;

Value::Value(Type type) : type(std::move(type)), primitiveValue({}) {}

Value::Value(const primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE>& value)
    : type(getMinBits(value)), primitiveValue({}) {}

Value::Value(const primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE>& value)
    : type(getMinBits(value)), primitiveValue({}) {}

Value::Value(const primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE>& value)
    : type(getMinBits(value)), primitiveValue({}) {}

Value::Value(Type type,
             const primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE>& value)
    : type(std::move(type)), primitiveValue({}) {
  primitiveValue.signedVal = value;
}

Value::Value(Type type,
             const primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE>& value)
    : type(std::move(type)), primitiveValue({}) {
  primitiveValue.unsignedVal = value;
}

Value::Value(Type type,
             const primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE>& value)
    : type(std::move(type)), primitiveValue({}) {
  primitiveValue.floatVal = value;
}

const Type& Value::getType() const {
  return type;
}
