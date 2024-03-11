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
#include "ssa/rule/ActualParameter.hpp"

namespace ssa {

class CallableExprAST : public ExprAST {
 public:
  CallableExprAST() = delete;
  explicit CallableExprAST(std::string callable, std::unique_ptr<ActualParameter> parameter);

  void add(std::unique_ptr<ExprAST> argument);

  Value codeGen() final;
  ExprAST::ExprType getType() const final;

  const std::string& getName() const;
  const ActualParameter& getParameter() const;

 private:
  std::string callable;
  std::unique_ptr<ActualParameter> parameter;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_CALLABLEEXPRAST_HPP
