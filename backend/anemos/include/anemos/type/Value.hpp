//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_VALUE_HPP
#define ANEMOS_VALUE_HPP

#include "ObjectReference.hpp"
#include "Type.hpp"

namespace anemos {
class Value {
 public:
  static Value makeSignedInteger(max_signed_integer_t value, Type type);
  static Value makeUnsignedInteger(max_unsigned_integer_t value, Type type);
  static Value makeF32(f32_t value);
  static Value makeF64(f64_t value);
  static Value makeUsize(usize_t value);
  static Value makeIsize(isize_t value);
  static Value makeObjectReference(ObjectReference value);

 private:
  Value();

  union Storage {
    max_unsigned_integer_t u_int;
    max_signed_integer_t i_int;
    f32_t f32;
    f64_t f64;
    usize_t usize;
    isize_t isize;

  } storage{};
  ObjectReference objectReference;
  Type type;
};

}  // namespace anemos

#endif  // ANEMOS_VALUE_HPP
