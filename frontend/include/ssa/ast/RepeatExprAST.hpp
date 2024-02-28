//
// Created by robcholz on 11/28/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_REPEATEXPRAST_HPP
#define SSAKURA_FRONTEND_REPEATEXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"

namespace ssa {
class RepeatExprAST : public ExprAST {
 public:
  enum class Type { REPEAT_UNTIL, REPEAT_TIMES };

  RepeatExprAST(Type repeatType,
                std::unique_ptr<ExprAST> conditionExpr,
                std::unique_ptr<ExprAST> bodyExpr);
  Value codeGen() final;
  ExprAST::Type getType() const final;

 private:
  Type repeatType;
  std::unique_ptr<ExprAST> conditionExpr;
  std::unique_ptr<ExprAST> bodyExpr;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_REPEATEXPRAST_HPP
