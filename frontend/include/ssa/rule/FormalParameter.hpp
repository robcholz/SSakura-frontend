//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_FORMALPARAMETER_HPP
#define SSAKURA_FRONTEND_FORMALPARAMETER_HPP

#include <memory>
#include <vector>
#include "VariableDeclaration.hpp"

namespace ssa {
class FormalParameter {
 public:
  bool operator==(const FormalParameter& other) const;

  void add(std::unique_ptr<VariableDeclaration> type);

  auto size() const { return parameters.size(); }

  auto begin() const { return parameters.begin(); }

  auto end() const { return parameters.end(); }

 private:
  std::vector<std::unique_ptr<VariableDeclaration>> parameters{};
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_FORMALPARAMETER_HPP
