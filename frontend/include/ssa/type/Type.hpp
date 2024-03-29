//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_TYPE_HPP
#define SSAKURA_FRONTEND_TYPE_HPP

#include <optional>
#include <string>
#include <string_view>
#include <variant>

#include "ssa/lang/Primitive.hpp"

namespace ssa {
class Type {
 public:
  Type(Primitive type);

  Type& operator=(Primitive type);
  bool operator==(const Type& other) const;

  uint64_t getBitWidth() const;
  bool isFloat() const;
  bool isInteger() const;
  bool isSigned() const;
  bool isSignedInteger() const;
  bool isUnsignedInteger() const;
  bool isVoid() const;
  bool isPrimitive() const;
  bool canBeImplicitlyCastedTo(const Type& type);

  std::optional<Primitive> getPrimitive() const;
  std::string toString() const;

  bool tryImplicitlyCastTo(const Type& type);

 private:
  uint64_t bitwidth;
  bool primitive;
  std::variant<Primitive, std::string> variantType;

  void initializeFrom(Primitive type);
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_TYPE_HPP
