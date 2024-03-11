//
// Created by robcholz on 2/28/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ACTUALPARAMETER_HPP
#define SSAKURA_FRONTEND_ACTUALPARAMETER_HPP

#include <vector>
#include <memory>
#include "ssa/ast/ExprAST.hpp"
#include "FormalParameter.hpp"

namespace ssa{
class ActualParameter {
 public:
  void add(std::unique_ptr<ExprAST> parameter);

  bool canCastToFormalParameter(const FormalParameter& formalParameter) const;

  auto size() const { return parameters.size(); }

  auto begin() const { return parameters.begin(); }

  auto end() const { return parameters.end(); }

 private:
  std::vector<std::unique_ptr<ExprAST>> parameters;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_ACTUALPARAMETER_HPP
