//
// Created by robcholz on 2/17/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_FRONTEND_ASTADAPTER_HPP
#define SSAKURA_FRONTEND_FRONTEND_ASTADAPTER_HPP

#include <functional>
#include <string_view>
#include "Attribute.hpp"
#include "ast/BlockExprAST.hpp"
#include "ast/CallableExprAST.hpp"
#include "ast/FunctionAST.hpp"
#include "ast/NumberExprAST.hpp"
#include "ast/ProtoTypeAST.hpp"
#include "ast/RepeatExprAST.hpp"

namespace ssa {
class AdapterRegistry;
class ASTAdapter {
 public:
  ASTAdapter() = delete;
  ~ASTAdapter() = delete;
  ASTAdapter& operator=(ASTAdapter&) = delete;

  static SSA_FORCE_INLINE Value blockExprGen();

  static SSA_FORCE_INLINE Value ifExprGen(const std::unique_ptr<ExprAST>& condition,
                         const std::unique_ptr<ExprAST>& thenExpr,
                         const std::unique_ptr<ExprAST>& elseExpr);

  static SSA_FORCE_INLINE Value callableExprGen(
      std::string_view callable,
      const std::vector<std::unique_ptr<ExprAST>>& arguments);

  static SSA_FORCE_INLINE Value functionExprGen(const std::unique_ptr<PrototypeAST>& prototype,
                               const std::unique_ptr<ExprAST>& body);

  static SSA_FORCE_INLINE Value repeatExprGen(RepeatExprAST::Type repeatType,
                             const std::unique_ptr<ExprAST>& conditionExpr,
                             const std::unique_ptr<ExprAST>& bodyExpr);

  static SSA_FORCE_INLINE Function prototypeExprGen(
      std::string_view name,
      const std::unique_ptr<ParameterList>& arguments,
      const std::unique_ptr<Type>& returnType);

  static SSA_FORCE_INLINE Value numberExprGen(const std::unique_ptr<VariableConstant>& constant);

  static SSA_FORCE_INLINE Value variableExprGen(std::string_view name);

 private:
  friend AdapterRegistry;

  static inline std::function<Value()> blockExprCallback;  // TODO
  static inline std::function<Value(const std::unique_ptr<ExprAST>&,
                      const std::unique_ptr<ExprAST>&,
                      const std::unique_ptr<ExprAST>&)>
      ifExprCallback;
  static inline std::function<Value(std::string_view,
                      const std::vector<std::unique_ptr<ExprAST>>&)>
      callableExprCallback;
  static inline std::function<Value(const std::unique_ptr<PrototypeAST>&,
                      const std::unique_ptr<ExprAST>&)>
      functionExprCallback;
  static inline std::function<Value(RepeatExprAST::Type,
                      const std::unique_ptr<ExprAST>&,
                      const std::unique_ptr<ExprAST>&)>
      repeatExprCallback;
  static inline std::function<Function(std::string_view,
                         const std::unique_ptr<ParameterList>&,
                         const std::unique_ptr<Type>&)>
      prototypeExprCallback;
  static inline std::function<Value(const std::unique_ptr<VariableConstant>&)>
      numberExprCallback;
  static inline std::function<Value(std::string_view)> variableExprCallback;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_FRONTEND_ASTADAPTER_HPP
