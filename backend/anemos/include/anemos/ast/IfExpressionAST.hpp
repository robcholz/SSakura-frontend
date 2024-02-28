//
// Created by robcholz on 2/19/24.
//
#pragma once

#ifndef ANEMOS_IFEXPRESSIONAST_HPP
#define ANEMOS_IFEXPRESSIONAST_HPP

#include <memory>
#include "ExpressionAST.hpp"

namespace anemos {
class IfExpressionAST : public ExpressionAST {
 public:
  explicit IfExpressionAST(std::unique_ptr<ExpressionAST> condition,
                           std::unique_ptr<ExpressionAST> thenBranch,
                           std::unique_ptr<ExpressionAST> elseBranch);

  void execute() final;

 private:
  std::unique_ptr<ExpressionAST> exprCondition;
  std::unique_ptr<ExpressionAST> exprThenBranch;
  std::unique_ptr<ExpressionAST> exprElseBranch;
};
}  // namespace anemos

#endif  // ANEMOS_IFEXPRESSIONAST_HPP
