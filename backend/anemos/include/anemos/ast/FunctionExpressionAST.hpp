//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef ANEMOS_FUNCTIONEXPRESSIONAST_HPP
#define ANEMOS_FUNCTIONEXPRESSIONAST_HPP

#include <memory>
#include <string>

#include "ExpressionAST.hpp"
#include "anemos/type/Parameter.hpp"
#include "anemos/type/Type.hpp"

namespace anemos {
class FunctionExpressionAST : public ExpressionAST {
 public:
  FunctionExpressionAST() = default;
  ~FunctionExpressionAST() override = default;

  void addName(std::string name);
  void addParameter(Parameter parameter);
  void addReturn(Type type);
  void addBody(std::unique_ptr<ExpressionAST> body);

  std::string getName() const;

  Value invoke(const Parameter& param);

  void execute() final;

 private:
  std::string funcName;
  Parameter parameter;
  Type returnType{Primitive::I32};
  std::unique_ptr<ExpressionAST> funcBody;
};
}  // namespace anemos

#endif  // ANEMOS_FUNCTIONEXPRESSIONAST_HPP
