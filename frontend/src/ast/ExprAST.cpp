//
// Created by robcholz on 3/10/24.
//
#include "ssa/ast/ExprAST.hpp"

using namespace ssa;

std::expected<ssa::Type, ExprAST::ExprType> ExprAST::hasReturnType() const {
  return std::unexpected(getType());
}
