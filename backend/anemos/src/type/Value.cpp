//
// Created by robcholz on 2/19/24.
//
#include "anemos/type/Value.hpp"

using namespace anemos;

Value::Value(const anemos::Value& value) : type(value.type) {
  this->storage = value.storage;
  this->objectReference = value.objectReference;
}

Value Value::makeSignedInteger(anemos::max_signed_integer_t value, Type type) {
  Value val;
  val.storage.i_int = value;
  val.type = std::move(type);
  return std::move(val);
}

Value Value::makeUnsignedInteger(anemos::max_unsigned_integer_t value,
                                 Type type) {
  Value val;
  val.storage.u_int = value;
  val.type = std::move(type);
  return std::move(val);
}

Value Value::makeF32(anemos::f32_t value) {
  Value val;
  val.storage.f32 = value;
  val.type = Primitive::F32;
  return std::move(val);
}

Value Value::makeF64(anemos::f64_t value) {
  Value val;
  val.storage.f64 = value;
  val.type = Primitive::F64;
  return std::move(val);
}

Value Value::makeIsize(anemos::isize_t value) {
  Value val;
  val.storage.isize = value;
  val.type = Primitive::ISIZE;
  return std::move(val);
}

Value Value::makeUsize(anemos::usize_t value) {
  Value val;
  val.storage.usize = value;
  val.type = Primitive::USIZE;
  return std::move(val);
}

Value Value::makeObjectReference(anemos::ObjectReference value) {
  Value val;
  val.objectReference = std::move(value);
  // TODO
  return std::move(val);
}


Value::Value() : type(Primitive::I8) {}
