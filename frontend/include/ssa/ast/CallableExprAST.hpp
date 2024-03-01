//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_CALLABLEEXPRAST_HPP
#define SSAKURA_FRONTEND_CALLABLEEXPRAST_HPP

#include <memory>
#include <string>
#include <vector>

#include "ExprAST.hpp"
#include "ssa/rule/FormalParameter.hpp"

namespace ssa {

class CallableExprAST : public ExprAST {
 public:
  explicit CallableExprAST(const std::string& callable, std::unique_ptr<FormalParameter> arguments);
  Value codeGen() final;
  ExprAST::Type getType() const final;

  const std::string& getName() const;
  const FormalParameter& getArguments() const;

 private:
  std::string callable;
  std::unique_ptr<FormalParameter> arguments;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_CALLABLEEXPRAST_HPP
