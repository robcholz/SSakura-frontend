//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLECONSTANT_HPP
#define SSAKURA_FRONTEND_VARIABLECONSTANT_HPP

#include "rule/Variable.hpp"
#include "value/Value.hpp"

namespace ssa {
class VariableConstant {
 public:
  explicit VariableConstant(const Type& type,
                            const std::string& name,
                            const Value& value);
  explicit VariableConstant(const Type& type, const Value& value);

  ~VariableConstant();
  const Value& getValue() const;
  const Type& getType() const;

 private:
  Variable* variable;
  VariableDefinition* uniqueDefinition;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLECONSTANT_HPP
