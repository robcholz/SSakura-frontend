//
// Created by robcholz on 12/19/23.
//
#include "ssa/rule/ParameterList.hpp"

using namespace ssa;

void ParameterList::add(std::unique_ptr<VariableDeclaration> type) {
  parameters.push_back(std::move(type));
}

size_t ParameterList::size() const {
  return parameters.size();
}
