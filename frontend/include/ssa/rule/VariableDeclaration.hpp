//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLEDECLARATION_HPP
#define SSAKURA_FRONTEND_VARIABLEDECLARATION_HPP

#include "ssa/type/Type.hpp"

namespace ssa {
class VariableDeclaration {
 public:
  explicit VariableDeclaration(std::string name, Type type);

  bool operator==(const VariableDeclaration& other) const;

  std::string getName()const;
  const Type& getType() const;

 private:
  std::string variableName;
  Type variableType;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLEDECLARATION_HPP
