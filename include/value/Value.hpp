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
  using VariantT = std::variant<s_u8_t,
                                s_u16_t,
                                s_u32_t,
                                s_u32_t,
                                s_u64_t,
                                s_i8_t,
                                s_i16_t,
                                s_i32_t,
                                s_i64_t,
                                s_usize_t,
                                s_isize_t,
                                s_f32_t,
                                s_f64_t,
                                s_char_t>;

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
