//
// Created by robcholz on 2/18/24.
//
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

Value ASTAdapter::blockExprGen() {
  if (blockExprCallback)
    return blockExprCallback();
  return Value{Primitive::I8};
}

Value ASTAdapter::ifExprGen(const std::unique_ptr<ExprAST>& condition,
                            const std::unique_ptr<ExprAST>& thenExpr,
                            const std::unique_ptr<ExprAST>& elseExpr) {
  if (ifExprCallback)
    return ifExprCallback(condition, thenExpr, elseExpr);
  return Value{Primitive::I8};
}

Value ASTAdapter::callableExprGen(
    std::string_view callable,
    const FormalParameter& arguments) {
  if (callableExprCallback)
    return callableExprCallback(callable, arguments);
  return Value{Primitive::I8};
}

Value ASTAdapter::functionExprGen(
    const std::unique_ptr<PrototypeAST>& prototype,
    const std::unique_ptr<BlockExprAST>& body) {
  if (functionExprCallback)
    return functionExprCallback(prototype, body);
  return Value{Primitive::I8};
}

Value ASTAdapter::repeatExprGen(RepeatExprAST::Type repeatType,
                                const std::unique_ptr<ExprAST>& conditionExpr,
                                const std::unique_ptr<ExprAST>& bodyExpr) {
  if (repeatExprCallback)
    return repeatExprCallback(repeatType, conditionExpr, bodyExpr);
  return Value{Primitive::I8};
}

Function ASTAdapter::prototypeExprGen(
    std::string_view name,
    const std::unique_ptr<FormalParameter>& arguments,
    const std::unique_ptr<Type>& returnType) {
  if (prototypeExprCallback)
    return prototypeExprCallback(name, arguments, returnType);
  return Function{};
}

Value ASTAdapter::numberExprGen(
    const std::unique_ptr<Value>& constant) {
  if (numberExprCallback)
    return numberExprCallback(constant);
  return Value{Primitive::I8};
}

Value ASTAdapter::variableExprGen(std::string_view name) {
  if (variableExprCallback)
    return variableExprCallback(name);
  return Value{Primitive::I8};
}
