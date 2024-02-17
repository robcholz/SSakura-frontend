//
// Created by robcholz on 2/1/24.
//
#include "rule/VariableDefinition.hpp"

using namespace ssa;

VariableDefinition::VariableDefinition(std::unique_ptr<Type> type,
                                       const std::string& name)
    : variableType(std::move(type)), variableName(name) {}

std::string VariableDefinition::getName() const {
  return variableName;
}

const Type& VariableDefinition::getType() const {
  return *variableType;
}