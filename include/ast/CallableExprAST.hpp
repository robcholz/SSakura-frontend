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

namespace ssa {

class CallableExprAST : public ExprAST {
 public:
  explicit CallableExprAST(const std::string& callable,
                           std::vector<std::unique_ptr<ExprAST>> arguments);
  Value codeGen() final;

 private:
  std::string callable;
  std::vector<std::unique_ptr<ExprAST>> arguments;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_CALLABLEEXPRAST_HPP
