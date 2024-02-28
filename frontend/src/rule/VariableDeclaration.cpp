//
// Created by robcholz on 2/1/24.
//
#include "ssa/rule/VariableDeclaration.hpp"

using namespace ssa;

VariableDeclaration::VariableDeclaration(std::string name,Value value)
    : variableName(std::move(name)),variableValue(std::move(value)) {}

std::string VariableDeclaration::getName() const {
  return variableName;
}

const Value& VariableDeclaration::getValue() const {
  return variableValue;
}