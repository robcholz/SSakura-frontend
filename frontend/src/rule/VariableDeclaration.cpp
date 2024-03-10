//
// Created by robcholz on 2/1/24.
//
#include "ssa/rule/VariableDeclaration.hpp"

using namespace ssa;

VariableDeclaration::VariableDeclaration(std::string name, Type type)
    : variableName(std::move(name)), variableType(std::move(type)) {}

bool VariableDeclaration::operator==(
    const ssa::VariableDeclaration& other) const {
  return variableName == other.variableName &&
         variableType == other.variableType;
}

std::string VariableDeclaration::getName() const {
  return variableName;
}

const Type& VariableDeclaration::getType() const {
  return variableType;
}