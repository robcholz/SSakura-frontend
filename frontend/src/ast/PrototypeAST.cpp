//
// Created by robcholz on 11/28/23.
//
#include "ssa/ast/ProtoTypeAST.hpp"
#include "ssa/Info.hpp"
#include "ssa/adapter/ASTAdapter.hpp"

using namespace ssa;

PrototypeAST::PrototypeAST(const std::string& name,
                           std::unique_ptr<FormalParameter> arguments,
                           std::unique_ptr<Type> returnType)
    : returnType(std::move(returnType)) {
  this->name = name;
  this->arguments = std::move(arguments);
}

std::string PrototypeAST::getName() const {
  return name;
}

const FormalParameter& PrototypeAST::getArguments() const {
  return *arguments;
}

const Type& PrototypeAST::getReturnType() const {
  return *returnType;
}

Function PrototypeAST::codeGen() {
  return ASTAdapter::prototypeExprGen(name, arguments, returnType);
}
