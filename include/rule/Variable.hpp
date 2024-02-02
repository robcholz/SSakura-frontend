//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLE_HPP
#define SSAKURA_FRONTEND_VARIABLE_HPP

#include "VariableDefinition.hpp"
#include "value/Value.hpp"

namespace ssa {
class Variable {
 public:
  explicit Variable(VariableDefinition* definition, const Value& value);
  void assign(const Value& value);
  const Value& getValue() const;

 private:
  VariableDefinition* variableDefinition;
  Value variableValue;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLE_HPP
