//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLE_HPP
#define SSAKURA_FRONTEND_VARIABLE_HPP

#include "VariableDeclaration.hpp"
#include "ssa/value/Value.hpp"

namespace ssa {
class Variable {
 public:
  explicit Variable(VariableDeclaration* definition, const Value& value);
  void assign(const Value& value);
  const Value& getValue() const;

 private:
  VariableDeclaration* variableDefinition;
  Value variableValue;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLE_HPP
