//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_EXPRAST_HPP
#define SSAKURA_FRONTEND_EXPRAST_HPP

#include "value/Value.hpp"

namespace ssa {
class ExprAST {
 public:
  virtual ~ExprAST() = default;

  virtual Value codeGen() = 0;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_EXPRAST_HPP
