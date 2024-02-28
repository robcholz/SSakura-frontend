//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_PARAMETER_HPP
#define ANEMOS_PARAMETER_HPP

#include <vector>
#include "VariableDeclaration.hpp"

namespace anemos {
class Parameter {
 public:
  template <typename... Args>
  explicit Parameter(const Args&... args) {
    parameters.reserve(sizeof...(Args));
    (parameters.push_back(args), ...);
  }

  void add(VariableDeclaration var) { parameters.push_back(std::move(var)); }

 private:
  std::vector<VariableDeclaration> parameters;
};
}  // namespace anemos

#endif  // ANEMOS_PARAMETER_HPP
