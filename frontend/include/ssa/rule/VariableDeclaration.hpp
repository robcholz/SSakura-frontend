//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLEDECLARATION_HPP
#define SSAKURA_FRONTEND_VARIABLEDECLARATION_HPP

#include "ssa/value/Value.hpp"

namespace ssa {
class VariableDeclaration {
 public:
  explicit VariableDeclaration(std::string name,Value value);

  std::string getName()const;
  const Value& getValue()const;

 private:
  std::string variableName;
  Value variableValue;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLEDECLARATION_HPP
