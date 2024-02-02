//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_PARAMETERLIST_HPP
#define SSAKURA_FRONTEND_PARAMETERLIST_HPP

#include <memory>
#include <vector>
#include "VariableDefinition.hpp"

namespace ssa {
class ParameterList {
 public:
  void add(std::unique_ptr<VariableDefinition> type);
  size_t size() const;

  // return a copy of parameters
  std::vector<VariableDefinition> getParameters() const;

  static ParameterList emptyParamList() { return ParameterList{}; }

 private:
  std::vector<std::unique_ptr<VariableDefinition>> parameters{};
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_PARAMETERLIST_HPP
