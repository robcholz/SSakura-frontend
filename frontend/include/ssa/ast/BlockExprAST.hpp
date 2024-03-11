//
// Created by robcholz on 2/2/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BLOCKEXPRAST_HPP
#define SSAKURA_FRONTEND_BLOCKEXPRAST_HPP

#include <vector>
#include "ExprAST.hpp"

namespace ssa {
class BlockExprAST : public ExprAST {
 public:
  BlockExprAST(std::unique_ptr<ExprAST> expr);
  void add(std::unique_ptr<ExprAST> expr);

  Value codeGen() final;

  ExprAST::ExprType getType() const final;

  auto begin() const { return blockExpr.begin(); }
  auto end() const { return blockExpr.end(); }

 private:
  std::vector<std::unique_ptr<ExprAST>> blockExpr;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_BLOCKEXPRAST_HPP
