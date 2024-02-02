//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLEDEFINITION_HPP
#define SSAKURA_FRONTEND_VARIABLEDEFINITION_HPP

#include <memory>
#include "type/Type.hpp"

namespace ssa {
class VariableDefinition {
 public:
  explicit VariableDefinition(std::unique_ptr<Type> type, const std::string& name);

  std::string getName()const;
  const Type& getType()const;

 private:
  std::unique_ptr<Type> variableType;
  std::string variableName;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLEDEFINITION_HPP
