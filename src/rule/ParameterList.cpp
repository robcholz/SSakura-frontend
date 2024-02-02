//
// Created by robcholz on 12/19/23.
//
#include "rule/ParameterList.hpp"

using namespace ssa;

void ParameterList::add(std::unique_ptr<VariableDefinition> type) {
  parameters.push_back(std::move(type));
}

size_t ParameterList::size() const {
  return parameters.size();
}

std::vector<VariableDefinition> ParameterList::getParameters() const {
  std::vector<VariableDefinition> params;
  for (const auto& element : parameters) {
    params.push_back(VariableDefinition{
        std::make_unique<Type>(element->getType()), element->getName()});
  }
  return std::move(params);
}
