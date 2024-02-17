//
// Created by robcholz on 2/1/24.
//
#include "lang/Primitive.hpp"
#include <cmath>
#include <limits>
#include <utility>

namespace ssa {
Primitive getMinBits(primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE> number) {
  // bits can only be 8,16,32,64
  static_assert(std::is_same<decltype(number), s_u64_t>::value);
  s_u64_t min_bits = std::ceil(std::log2(number + 1));
  min_bits = (min_bits / 8 + 1) * 8;
  if (min_bits == 8)
    return (Primitive::U8);
  if (min_bits == 16)
    return (Primitive::U16);
  if (min_bits == 32)
    return (Primitive::U32);
  return (Primitive::U64);
}

Primitive getMinBits(primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE> number) {
  // bits can only be 8,16,32,64
  static_assert(std::is_same<decltype(number), s_i64_t>::value);
  s_u64_t min_bits = std::ceil(std::log2(std::abs(number)) + 1);
  min_bits = (min_bits / 8 + 1) * 8;
  if (min_bits == 8)
    return (Primitive::I8);
  if (min_bits == 16)
    return (Primitive::I16);
  if (min_bits == 32)
    return (Primitive::I32);
  return (Primitive::I64);
}

Primitive getMinBits(primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE> number) {
  static_assert(std::is_same<decltype(number), s_f64_t>::value);
  static const s_f64_t F32_MIN = std::numeric_limits<s_f32_t>::min();
  static const s_f64_t F32_MAX = std::numeric_limits<s_f32_t>::max();
  static const s_f64_t F64_MIN = std::numeric_limits<s_f64_t>::min();
  static const s_f64_t F64_MAX = std::numeric_limits<s_f64_t>::max();

  if (F32_MIN <= number && number <= F32_MAX)
    return (Primitive::F32);
  return (Primitive::F64);
}

s_u64_t getBitwidth(Primitive type) {
  switch (type) {
    case Primitive::U8:
      return 8;
    case Primitive::I8:
      return 8;
    case Primitive::U16:
      return 16;
    case Primitive::I16:
      return 16;
    case Primitive::U32:
      return 32;
    case Primitive::I32:
      return 32;
    case Primitive::F32:
      return 32;
    case Primitive::U64:
      return 64;
    case Primitive::I64:
      return 64;
    case Primitive::F64:
      return 32;
    case Primitive::USIZE:
      return sizeof(s_usize_t);
    case Primitive::ISIZE:
      return sizeof(s_isize_t);
    case Primitive::VOID:
      return 0;
    case Primitive::NONE:
      return 0;
  }
}

namespace internal {
std::unordered_map<std::string, Primitive> _elementMap_s2e;
std::unordered_map<Primitive, std::string> _elementMap_e2s;
}  // namespace internal
}  // namespace ssa