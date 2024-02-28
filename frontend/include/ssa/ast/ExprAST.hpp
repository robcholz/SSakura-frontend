//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_EXPRAST_HPP
#define SSAKURA_FRONTEND_EXPRAST_HPP

#include "ssa/value/Value.hpp"

namespace ssa {
class ExprAST {
 public:
  enum class Type {
    BINARY_EXPR,
    BLOCK_EXPR,
    CALLABLE_EXPR,
    FUNCTION_EXPR,
    IF_EXPR,
    NUMBER_EXPR,
    REPEAT_EXPR,
    VARIABLE_EXPR,
  };

  virtual ~ExprAST() = default;

  virtual Value codeGen() = 0;
  virtual ExprAST::Type getType() const = 0;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_EXPRAST_HPP
