//
// Created by robcholz on 1/30/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_PRIMITIVE_HPP
#define SSAKURA_FRONTEND_PRIMITIVE_HPP

#include <spdlog/spdlog.h>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

namespace ssa {

enum class Primitive {
  I8,
  I16,
  I32,
  I64,
  ISIZE,
  U8,
  U16,
  U32,
  U64,
  USIZE,
  F32,
  F64,
  VOID,
  NONE,
};

using s_f32_t = float;
using s_f64_t = double;

using s_u8_t = uint8_t;
using s_u16_t = uint16_t;
using s_u32_t = uint32_t;
using s_u64_t = uint64_t;

using s_i8_t = int8_t;
using s_i16_t = int16_t;
using s_i32_t = int32_t;
using s_i64_t = int64_t;

using s_usize_t = std::uintptr_t;
using s_isize_t = std::ptrdiff_t;

using s_char_t = char;  // TODO use utf8 later

namespace internal {
template <Primitive>
struct PrimitiveTypeEnumToType {};

template <>
struct PrimitiveTypeEnumToType<Primitive::F32> {
  using type = s_f32_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::F64> {
  using type = s_f64_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::USIZE> {
  using type = s_usize_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::ISIZE> {
  using type = s_isize_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::I8> {
  using type = s_i8_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::I16> {
  using type = s_i16_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::I32> {
  using type = s_i32_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::I64> {
  using type = s_i64_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::U8> {
  using type = s_u8_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::U16> {
  using type = s_u16_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::U32> {
  using type = s_u32_t;
};

template <>
struct PrimitiveTypeEnumToType<Primitive::U64> {
  using type = s_u64_t;
};

extern std::unordered_map<std::string, Primitive> _elementMap_s2e;
extern std::unordered_map<Primitive, std::string> _elementMap_e2s;
}  // namespace internal

template <Primitive EnumValue>
using primitiveTypeEnumToType =
    typename internal::PrimitiveTypeEnumToType<EnumValue>::type;

template <typename TYPE>
static constexpr Primitive typeToPrimitiveTypeEnum() {
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::F32>>)
    return Primitive::F32;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::F64>>)
    return Primitive::F64;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::USIZE>>)
    return Primitive::USIZE;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::ISIZE>>)
    return Primitive::ISIZE;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U8>>)
    return Primitive::U8;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U16>>)
    return Primitive::U16;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U32>>)
    return Primitive::U32;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U64>>)
    return Primitive::U64;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I8>>)
    return Primitive::I8;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I16>>)
    return Primitive::I16;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I32>>)
    return Primitive::I32;
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I64>>)
    return Primitive::I64;
  // impossible situation, just to silent the compiler!
  return Primitive::I64;
}

template <typename TYPE>
static constexpr bool isArch() {
  if constexpr (std::is_same_v<TYPE,
                               primitiveTypeEnumToType<Primitive::USIZE>> ||
                std::is_same_v<TYPE,
                               primitiveTypeEnumToType<Primitive::ISIZE>>) {
    return true;
  }
  return false;
}

template <typename TYPE>
static constexpr bool isFloatType() {
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::F32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::F64>>) {
    return true;
  }
  return false;
}

template <typename TYPE>
static constexpr bool isUnsignedType() {
  if constexpr (std::is_same_v<TYPE,
                               primitiveTypeEnumToType<Primitive::USIZE>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U8>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U16>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U64>>) {
    return true;
  }
  return false;
}

template <typename TYPE>
static constexpr bool isSignedType() {
  if constexpr (std::is_same_v<TYPE,
                               primitiveTypeEnumToType<Primitive::ISIZE>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I8>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I16>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I64>>) {
    return true;
  }
  return false;
}

template <typename TYPE>
static constexpr bool isPureIntegerType() {
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U8>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U16>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U64>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I8>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I16>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I64>>) {
    return true;
  }
  return false;
}

template <typename TYPE>
static constexpr bool isPrimitiveType() {
  if constexpr (isArch<TYPE>() || isFloatType<TYPE>() ||
                isUnsignedType<TYPE>() ||
                isSignedType<TYPE>() || isPureIntegerType<TYPE>())
    return true;
  return false;
}

constexpr Primitive MAX_SIGNED_PRIMITIVE = Primitive::I64;

constexpr Primitive MAX_UNSIGNED_PRIMITIVE = Primitive::U64;

constexpr Primitive MAX_FLOAT_PRIMITIVE = Primitive::F64;

extern Primitive getMinBits(primitiveTypeEnumToType<MAX_SIGNED_PRIMITIVE> number);

extern Primitive getMinBits(primitiveTypeEnumToType<MAX_UNSIGNED_PRIMITIVE> number);

extern Primitive getMinBits(primitiveTypeEnumToType<MAX_FLOAT_PRIMITIVE> number);

extern s_u64_t getBitwidth(Primitive type);

template <typename T>
static std::optional<T> from_string(const std::string& key);

template <>
std::optional<Primitive> from_string(const std::string& key) {
  if (internal::_elementMap_s2e.contains(key))
    return std::make_optional(internal::_elementMap_s2e.at(key));
  spdlog::error("No keyword found in s2e map");
  return std::nullopt;
}

static std::string to_string(Primitive elementary) {
  return internal::_elementMap_e2s.at(elementary);
}
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_PRIMITIVE_HPP
