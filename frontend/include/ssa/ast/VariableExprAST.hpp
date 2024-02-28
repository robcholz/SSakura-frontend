//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLEEXPRAST_HPP
#define SSAKURA_FRONTEND_VARIABLEEXPRAST_HPP

#include <string>
#include "ExprAST.hpp"

namespace ssa {
class VariableExprAST : public ExprAST {
 public:
  explicit VariableExprAST(const std::string& name);
  Value codeGen() final;

  std::string getName() const;
  ExprAST::Type getType() const final;

 private:
  std::string name;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VARIABLEEXPRAST_HPP
