//
// Created by robcholz on 3/10/24.
//
#include <utility>

#include "ssa/rule/ActualParameter.hpp"

using namespace ssa;

ActualParameter::ActualParameter(const std::string& name, Value value)
    : value(std::move(value)) {
  this->name = name;
}

ActualParameter::ActualParameter(Value value) : value(std::move(value)) {
  this->name = "";
}

FormalParameter ActualParameter::toFormalParameter() const {
  FormalParameter formalParameter;
  formalParameter.add(
      std::make_unique<VariableDeclaration>(name, value.getType()));
  return formalParameter;
}

const Value& ActualParameter::getValue() const {
  return value;
}

const std::string& ActualParameter::getName() const {
  return name;
}
