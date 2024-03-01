//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_FUNCTIONREGISTRY_HPP
#define ANEMOS_FUNCTIONREGISTRY_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <string_view>
#include <optional>
#include "anemos/ast/FunctionExpressionAST.hpp"

namespace anemos {
class FunctionRegistry {
 public:
  FunctionRegistry& operator=(FunctionRegistry&) = delete;
  FunctionRegistry& operator=(FunctionRegistry&&) = delete;

  static FunctionRegistry& getInstance(){
    static FunctionRegistry registry;
    return registry;
  }

  void add(std::unique_ptr<FunctionExpressionAST> function);

  bool contains(const FunctionExpressionAST& functionExpressionAst) const;

  std::optional<Value> invoke(const std::string& function,const FormalParameter& parameter) const;

 private:
  FunctionRegistry() = default;
  ~FunctionRegistry() = default;

  std::unordered_map<std::string, FunctionExpressionAST*> registry;
};
}  // namespace anemos

#endif  // ANEMOS_FUNCTIONREGISTRY_HPP
