//
// Created by robcholz on 1/30/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VALUE_HPP
#define SSAKURA_FRONTEND_VALUE_HPP

#include "type/Type.hpp"

namespace ssa {
class Value {
 private:
  /// use the maximum size of each type for simplicity
  using VariantT = std::variant<primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE>,
                                primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE>,
                                primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE>
                                >;

 public:
  explicit Value(const VariantT& value);
  explicit Value(const Type& type,const VariantT& value);
  Value& operator=(const VariantT& value);

  template <typename T>
  std::optional<T> getValue() const {
    static_assert(isPrimitiveType<T>());
    if (!type.isPrimitive())
      return std::nullopt;
    return std::make_optional(std::get<T>(primitiveValue));
  }

  const Type& getType() const;

 private:
  VariantT primitiveValue;
  Type type;

  template <typename TYPE>
  void initializeFrom(const TYPE& value) {
    this->primitiveValue = value;
    this->type = typeToPrimitiveTypeEnum<TYPE>();
  }
};

}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VALUE_HPP
