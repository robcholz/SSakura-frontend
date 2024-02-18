//
// Created by robcholz on 2/18/24.
//
#include "adapter/ASTAdapter.hpp"

using namespace ssa;

Value ASTAdapter::blockExprGen() {
  return blockExprCallback();
}

Value ASTAdapter::ifExprGen(const std::unique_ptr<ExprAST>& condition,
                            const std::unique_ptr<ExprAST>& thenExpr,
                            const std::unique_ptr<ExprAST>& elseExpr) {
  return ifExprCallback(condition, thenExpr, elseExpr);
}

Value ASTAdapter::callableExprGen(
    std::string_view callable,
    const std::vector<std::unique_ptr<ExprAST>>& arguments) {
  return callableExprCallback(callable, arguments);
}

Value ASTAdapter::functionExprGen(
    const std::unique_ptr<PrototypeAST>& prototype,
    const std::unique_ptr<ExprAST>& body) {
  return functionExprCallback(prototype, body);
}

Value ASTAdapter::repeatExprGen(RepeatExprAST::Type repeatType,
                                const std::unique_ptr<ExprAST>& conditionExpr,
                                const std::unique_ptr<ExprAST>& bodyExpr) {
  return repeatExprCallback(repeatType, conditionExpr, bodyExpr);
}

Function ASTAdapter::prototypeExprGen(
    std::string_view name,
    const std::unique_ptr<ParameterList>& arguments,
    const std::unique_ptr<Type>& returnType) {
  return prototypeExprCallback(name, arguments, returnType);
}

Value ASTAdapter::numberExprGen(
    const std::unique_ptr<VariableConstant>& constant) {
  return numberExprCallback(constant);
}

Value ASTAdapter::variableExprGen(std::string_view name) {
  return variableExprCallback(name);
}
