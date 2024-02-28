//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_PARAMETERLIST_HPP
#define SSAKURA_FRONTEND_PARAMETERLIST_HPP

#include <memory>
#include <vector>
#include "VariableDeclaration.hpp"

namespace ssa {
class ParameterList {
 public:
  void add(std::unique_ptr<VariableDeclaration> type);
  size_t size() const;

  static ParameterList emptyParamList() { return ParameterList{}; }

  auto begin() const { return parameters.begin(); }

  auto end() const { return parameters.end(); }

 private:
  std::vector<std::unique_ptr<VariableDeclaration>> parameters{};
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_PARAMETERLIST_HPP
