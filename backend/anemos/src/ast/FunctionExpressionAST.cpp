//
// Created by robcholz on 2/18/24.
//
#include "anemos/ast/FunctionExpressionAST.hpp"

using namespace anemos;

void FunctionExpressionAST::addName(std::string name) {
  this->funcName = std::move(name);
}

void FunctionExpressionAST::addParameter(anemos::FormalParameter param) {
  this->parameter = std::move(param);
}

void FunctionExpressionAST::addReturn(anemos::Type type) {
  this->returnType = std::move(type);
}

void FunctionExpressionAST::addBody(std::unique_ptr<ExpressionAST> body) {
  this->funcBody = std::move(body);
}

std::string FunctionExpressionAST::getName() const {
  return this->funcName;
}

Value FunctionExpressionAST::invoke(const anemos::FormalParameter& param) {
  return Value::makeF32(0);
}

void FunctionExpressionAST::execute() {}