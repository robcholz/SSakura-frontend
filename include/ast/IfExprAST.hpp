//
// Created by robcholz on 11/28/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_IFEXPRAST_HPP
#define SSAKURA_FRONTEND_IFEXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"

namespace ssa {
class IfExprAST : public ExprAST {
 public:
  IfExprAST(std::unique_ptr<ExprAST> condition,
            std::unique_ptr<ExprAST> thenExpr,
            std::unique_ptr<ExprAST> elseExpr);

  Value codeGen() final;

 private:
  std::unique_ptr<ExprAST> condition;
  std::unique_ptr<ExprAST> thenExpr;
  std::unique_ptr<ExprAST> elseExpr;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_IFEXPRAST_HPP
