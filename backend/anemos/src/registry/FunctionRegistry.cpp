//
// Created by robcholz on 2/28/24.
//
#include "anemos/registry/FunctionRegistry.hpp"

using namespace anemos;

void FunctionRegistry::add(std::unique_ptr<FunctionExpressionAST> function) {
  registry.insert({function->getName(), std::move(function).release()});
}

bool FunctionRegistry::contains(
    const FunctionExpressionAST& functionExpressionAst) const {
  return registry.contains(functionExpressionAst.getName());
}

std::optional<Value> FunctionRegistry::invoke(const std::string& function,
                              const FormalParameter& parameter) const {
  if(registry.contains(function)){
    return std::make_optional(registry.at(function)->invoke(parameter));
  }
  return std::nullopt;
}