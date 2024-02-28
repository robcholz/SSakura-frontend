//
// Created by robcholz on 2/19/24.
//
#pragma once

#ifndef ANEMOS_NUMBEREXPRESSIONAST_HPP
#define ANEMOS_NUMBEREXPRESSIONAST_HPP

#include "ExpressionAST.hpp"
#include "anemos/type/Value.hpp"

namespace anemos {
class NumberExpressionAST : public ExpressionAST {
 public:
  explicit NumberExpressionAST(Value val);

  void execute() final;

 private:
  Value value;
};
}  // namespace anemos

#endif  // ANEMOS_NUMBEREXPRESSIONAST_HPP
