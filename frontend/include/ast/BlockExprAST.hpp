//
// Created by robcholz on 2/2/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BLOCKEXPRAST_HPP
#define SSAKURA_FRONTEND_BLOCKEXPRAST_HPP

#include "ExprAST.hpp"

namespace ssa {
class BlockExprAST : public ExprAST {
 public:
  Value codeGen()final;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_BLOCKEXPRAST_HPP
