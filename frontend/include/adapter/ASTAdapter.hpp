//
// Created by robcholz on 2/17/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_FRONTEND_ASTADAPTER_HPP
#define SSAKURA_FRONTEND_FRONTEND_ASTADAPTER_HPP

#include <string_view>
#include "ast/BlockExprAST.hpp"
#include "ast/CallableExprAST.hpp"
#include "ast/FunctionAST.hpp"
#include "ast/NumberExprAST.hpp"
#include "ast/ProtoTypeAST.hpp"
#include "ast/RepeatExprAST.hpp"

namespace ssa {
class ASTAdapter {
 public:
  ASTAdapter() = delete;
  ~ASTAdapter() = delete;
  ASTAdapter& operator=(ASTAdapter&) = delete;

  static Value blockExprGen() {return Value{1};}

  static Value ifExprGen(const auto& condition,
                         const auto& thenExpr,
                         const auto& elseExpr) {return Value{1};}

  static Value callableExprGen(
      std::string_view callable,
      const std::vector<std::unique_ptr<ExprAST>>& arguments) {return Value{1};}

  static Value functionExprGen(const std::unique_ptr<PrototypeAST>& prototype,
                               const std::unique_ptr<ExprAST>& body) {return Value{1};}

  static Value repeatExprGen(RepeatExprAST::Type repeatType,
                             const std::unique_ptr<ExprAST>& conditionExpr,
                             const std::unique_ptr<ExprAST>& bodyExpr) {return Value{1};}

  static Function prototypeExprGen(
      std::string_view name,
      const std::unique_ptr<ParameterList>& arguments,
      const std::unique_ptr<Type>& returnType) {return Function{};}

  static Value numberExprGen(
      const std::unique_ptr<VariableConstant>& constant) {return Value{1};}

  static Value variableExprGen(std::string_view name){return Value{1};}
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_FRONTEND_ASTADAPTER_HPP
