//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_TYPE_HPP
#define ANEMOS_TYPE_HPP

#include <string>
#include "Primitive.hpp"

namespace anemos {
class Type {
 public:
  Type(Primitive type);
  Type(const std::string& type);

  std::string getCustomType() const;
  Primitive getPrimitiveType() const;

  bool isPrimitive() const;

 private:
  bool primitive;
  std::string customType;
  Primitive primitiveType;
};
}  // namespace anemos

#endif  // ANEMOS_TYPE_HPP
