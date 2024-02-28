//
// Created by robcholz on 2/27/24.
//
#pragma once

#ifndef ANEMOS_BLOCKEXPRESSIONAST_HPP
#define ANEMOS_BLOCKEXPRESSIONAST_HPP

#include <memory>
#include <vector>
#include "ExpressionAST.hpp"

namespace anemos {
class BlockExpressionAST : public ExpressionAST {
 public:
  explicit BlockExpressionAST(
      std::vector<std::unique_ptr<ExpressionAST>> expressions);

  void execute() final;

 private:
  std::vector<std::unique_ptr<ExpressionAST>> exprExpressions;
};
}  // namespace anemos

#endif  // ANEMOS_BLOCKEXPRESSIONAST_HPP
