//
// Created by robcholz on 2/1/24.
//
#include "rule/Variable.hpp"

using namespace ssa;

Variable::Variable(ssa::VariableDefinition* definition,
                   const ssa::Value& value):variableDefinition(definition), variableValue(value) {
}

void Variable::assign(const ssa::Value& value) {
  this->variableValue = value;
}

const Value& Variable::getValue() const {
  return variableValue;
}