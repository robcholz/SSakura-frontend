//
// Created by robcholz on 2/18/24.
//
#include "anemos/type/Type.hpp"

using namespace anemos;

Type::Type(anemos::Primitive type) {
  this->primitive = true;
  this->primitiveType = type;
}

Type::Type(const std::string& type) {
  this->primitive = false;
  this->customType = type;

  this->primitiveType = decltype(primitiveType){};
}

std::string Type::getCustomType() const {
  return customType;
}

Primitive Type::getPrimitiveType() const {
  return primitiveType;
}

bool Type::isPrimitive() const {
  return primitive;
}