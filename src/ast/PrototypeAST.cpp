//
// Created by robcholz on 11/28/23.
//
#include "ast/ProtoTypeAST.hpp"
#include "Info.hpp"

using namespace ssa;

PrototypeAST::PrototypeAST(const std::string& name,
                           std::unique_ptr<ParameterList> arguments,
                           std::unique_ptr<Type> returnType)
    : returnType(std::move(returnType)) {
  this->name = name;
  this->arguements = std::move(arguments);
}

std::string PrototypeAST::getName() const {
  return name;
}

const Type& PrototypeAST::getReturnType() const {
  return *returnType;
}

Function PrototypeAST::codeGen() {}
