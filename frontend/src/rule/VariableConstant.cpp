//
// Created by robcholz on 2/1/24.
//
#include "ssa/rule/VariableConstant.hpp"

using namespace ssa;

VariableConstant::VariableConstant(const std::string& name,
                                   const Value& value) {
  this->uniqueDefinition =
      new VariableDeclaration(name,Primitive::I8); // TODO
  this->variable = new Variable(uniqueDefinition, value);
}

VariableConstant::VariableConstant(const ssa::Type& type,
                                   const ssa::Value& value) {
  this->uniqueDefinition =
      new VariableDeclaration("",type);
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
  return variable->getValue().getType();
}