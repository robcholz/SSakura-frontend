//
// Created by robcholz on 11/28/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_IFEXPRAST_HPP
#define SSAKURA_FRONTEND_IFEXPRAST_HPP

#include <memory>
#include <functional>
#include "ExprAST.hpp"

namespace ssa {
class IfExprAST : public ExprAST {
 public:
  IfExprAST(std::unique_ptr<ExprAST> condition,
            std::unique_ptr<ExprAST> thenExpr,
            std::unique_ptr<ExprAST> elseExpr);

  const ExprAST& getCondition() const;
  const ExprAST& getThenBranch() const;
  std::optional<std::reference_wrapper<const ExprAST>> getElseBranch() const;

  Value codeGen() final;
  ExprAST::Type getType() const final;

 private:
  std::unique_ptr<ExprAST> condition;
  std::unique_ptr<ExprAST> thenExpr;
  std::unique_ptr<ExprAST> elseExpr;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_IFEXPRAST_HPP
