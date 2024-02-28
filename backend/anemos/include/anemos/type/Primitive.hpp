//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_PRIMITIVE_HPP
#define ANEMOS_PRIMITIVE_HPP

#include <cstdint>
#include <cstddef>

namespace anemos {
using max_unsigned_integer_t = std::uint64_t;
using max_signed_integer_t = std::int64_t;
using f32_t = float;
using f64_t = double;
using usize_t = std::uintptr_t;
using isize_t = std::ptrdiff_t;

enum class Primitive{
  I8,
  I16,
  I32,
  I64,
  U8,
  U16,
  U32,
  U64,
  BYTE,
  CHAR,
  ISIZE,
  USIZE,
  F32,
  F64,
  BOOLEAN,
  VOID,
};
}  // namespace anemos

#endif  // ANEMOS_PRIMITIVE_HPP
