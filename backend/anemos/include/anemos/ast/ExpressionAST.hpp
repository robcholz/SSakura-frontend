//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_EXPRESSIONAST_HPP
#define ANEMOS_EXPRESSIONAST_HPP

namespace anemos {
class ExpressionAST {
 public:
  virtual ~ExpressionAST() = default;
  virtual void execute() = 0;
};
}  // namespace anemos

#endif  // ANEMOS_EXPRESSIONAST_HPP
