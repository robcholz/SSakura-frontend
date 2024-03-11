//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_EXPRAST_HPP
#define SSAKURA_FRONTEND_EXPRAST_HPP

#include <expected>
#include "ssa/value/Value.hpp"

namespace ssa {
class ExprAST {
 public:
  enum class ExprType {
    BINARY_EXPR,
    BLOCK_EXPR,
    CALLABLE_EXPR,
    FUNCTION_EXPR,
    IF_EXPR,
    NUMBER_EXPR,
    REPEAT_EXPR,
    VARIABLE_EXPR,
    VMINTERFACE_EXPR,
  };

  virtual ~ExprAST() = default;

  virtual Value codeGen(){return
      Value(Primitive::I8);}
  virtual ExprAST::ExprType getType() const = 0;
  virtual std::expected<ssa::Type, ExprType> hasReturnType() const;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_EXPRAST_HPP
