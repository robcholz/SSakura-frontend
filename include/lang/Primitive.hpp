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

using s_usize_t = std::size_t;
using s_isize_t = std::make_signed<s_usize_t>;

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
static Primitive typeToPrimitiveTypeEnum() {
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
}

template <typename TYPE>
static bool isPrimitiveType() {
  if constexpr (std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::F32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::F64>> ||
                std::is_same_v<TYPE,
                               primitiveTypeEnumToType<Primitive::USIZE>> ||
                std::is_same_v<TYPE,
                               primitiveTypeEnumToType<Primitive::ISIZE>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U8>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U16>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::U64>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I8>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I16>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I32>> ||
                std::is_same_v<TYPE, primitiveTypeEnumToType<Primitive::I64>>)
    return true;
  return false;
}

extern Primitive getMinBits(s_i64_t number);

extern Primitive getMinBits(s_u64_t number);

extern Primitive getMinBits(s_f64_t number);

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

static std::string to_string(Primitive elementary){
  return internal::_elementMap_e2s.at(elementary);
}
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_PRIMITIVE_HPP
