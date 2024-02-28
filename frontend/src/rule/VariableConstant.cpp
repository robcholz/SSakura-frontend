//
// Created by robcholz on 2/1/24.
//
#include "ssa/rule/VariableConstant.hpp"

using namespace ssa;

VariableConstant::VariableConstant(const Type& type,
                                   const std::string& name,
                                   const Value& value) {
  this->uniqueDefinition =
      new VariableDeclaration(name,value);
  this->variable = new Variable(uniqueDefinition, value);
}

VariableConstant::VariableConstant(const ssa::Type& type,
                                   const ssa::Value& value) {
  this->uniqueDefinition =
      new VariableDeclaration("",value);
  this->variable = new Variable(uniqueDefinition, value);
}

VariableConstant::~VariableConstant() {
  delete variable;
  delete uniqueDefinition;
}

const Value& VariableConstant::getValue() const {
  return variable->getValue();
}

const Type& VariableConstant::getType() const {
  return uniqueDefinition->getValue().getType();
}