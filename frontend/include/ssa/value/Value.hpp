//
// Created by robcholz on 1/30/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VALUE_HPP
#define SSAKURA_FRONTEND_VALUE_HPP

#include "ssa/type/Type.hpp"

namespace ssa {
class Value {
 public:
  Value(Type type);
  Value(const primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE>& value);
  Value(const primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE>& value);
  Value(const primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE>& value);
  Value(Type type, const primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE>& value);
  Value(Type type,
        const primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE>& value);
  Value(Type type, const primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE>& value);

  template <typename T>
  std::optional<T> getValue() const {
    static_assert(isPrimitiveType<T>());
    if (!type.isPrimitive())
      return std::nullopt;
    if constexpr (isFloatType<T>())
      return std::make_optional(
          static_cast<T>(primitiveValue.floatVal));
    if constexpr (isSignedType<T>())
      return std::make_optional(static_cast<T>(primitiveValue.signedVal));
    if constexpr (isUnsignedType<T>())
      return std::make_optional(static_cast<T>(primitiveValue.unsignedVal));
  }

  const Type& getType() const;

 private:
  /// use the maximum size of each type for simplicity
  union Storage {
    primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE> signedVal;
    primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE> unsignedVal;
    primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE> floatVal;
  };
  Storage primitiveValue;
  Type type;
};

}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VALUE_HPP
