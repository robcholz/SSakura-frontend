//
// Created by robcholz on 12/19/23.
//
#include "ssa/type/Type.hpp"
#include "ssa/Info.hpp"
#include "ssa/lang/Primitive.hpp"

using namespace ssa;

Type::Type(Primitive type) : bitwidth(0), primitive(false) {
  initializeFrom(type);
}

Type& Type::operator=(Primitive type) {
  initializeFrom(type);
  return *this;
}

bool Type::operator==(const Type& other) const {
  if (isPrimitive() != other.isPrimitive())
    return false;
  if (isPrimitive()) {
    return getPrimitive().value() == other.getPrimitive().value();
  }
  return std::get<std::string>(variantType) == std::get<std::string>(other.variantType);
}

uint64_t Type::getBitWidth() const {
  return bitwidth;
}

bool Type::isFloat() const {
  const auto& maybe_primitive = getPrimitive();
  if (!maybe_primitive.has_value())
    return false;
  const auto primitive_type = maybe_primitive.value();
  switch (primitive_type) {
    case Primitive::F32:
      return true;
    case Primitive::F64:
      return true;
    default:
      return false;
  }
}

bool Type::isInteger() const {
  const auto& maybe_primitive = getPrimitive();
  if (!maybe_primitive.has_value())
    return false;
  const auto primitive_type = maybe_primitive.value();
  switch (primitive_type) {
    case Primitive::I8:
      return true;
    case Primitive::I16:
      return true;
    case Primitive::I32:
      return true;
    case Primitive::I64:
      return true;
    case Primitive::U8:
      return true;
    case Primitive::U16:
      return true;
    case Primitive::U32:
      return true;
    case Primitive::U64:
      return true;
    case Primitive::ISIZE:
      return true;
    case Primitive::USIZE:
      return true;
    default:
      return false;
  }
}

bool Type::isPrimitive() const {
  return primitive;
}

bool Type::isSigned() const {
  if (isFloat())
    return true;
  if (isSignedInteger())
    return true;
  return false;
}

bool Type::isSignedInteger() const {
  const auto& maybe_primitive = getPrimitive();
  if (!maybe_primitive.has_value())
    return false;
  const auto primitive_type = maybe_primitive.value();
  switch (primitive_type) {
    case Primitive::I8:
      return true;
    case Primitive::I16:
      return true;
    case Primitive::I32:
      return true;
    case Primitive::I64:
      return true;
    case Primitive::ISIZE:
      return true;
    default:
      return false;
  }
}

bool Type::isUnsignedInteger() const {
  const auto& maybe_primitive = getPrimitive();
  if (!maybe_primitive.has_value())
    return false;
  const auto primitive_type = maybe_primitive.value();
  switch (primitive_type) {
    case Primitive::U8:
      return true;
    case Primitive::U16:
      return true;
    case Primitive::U32:
      return true;
    case Primitive::U64:
      return true;
    case Primitive::USIZE:
      return true;
    default:
      return false;
  }
}

bool Type::isVoid() const {
  const auto& maybe_primitive = getPrimitive();
  if (!maybe_primitive.has_value())
    return false;
  const auto primitive_type = maybe_primitive.value();
  return primitive_type == Primitive::VOID;
}

bool Type::canBeImplicitlyCastedTo(const ssa::Type& type) {
  if (!isPrimitive())
    return false;
  const auto& bitwidth_type = type.getBitWidth();
  return getBitWidth() <= bitwidth_type;
}

std::optional<Primitive> Type::getPrimitive() const {
  if (isPrimitive())
    return std::get<Primitive>(variantType);
  return std::nullopt;
}

std::string Type::toString() const {
  const auto& maybe_primitive = getPrimitive();
  if (maybe_primitive.has_value()) {
    return to_string(maybe_primitive.value());
  } else {
    return std::get<std::string>(this->variantType);
  }
}

bool Type::tryImplicitlyCastTo(const ssa::Type& type) {
  if (!canBeImplicitlyCastedTo(type))
    return false;
  this->bitwidth = type.getBitWidth();
  this->variantType = type.getPrimitive().value();
  return true;
}

void Type::initializeFrom(Primitive type) {
  this->primitive = true;
  this->variantType = type;
  this->bitwidth = getBitwidth(type);
}