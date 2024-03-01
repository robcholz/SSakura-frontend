//
// Created by robcholz on 12/19/23.
//
#include "ssa/rule/FormalParameter.hpp"

using namespace ssa;

void FormalParameter::add(std::unique_ptr<VariableDeclaration> type) {
  parameters.push_back(std::move(type));
}

size_t FormalParameter::size() const {
  return parameters.size();
}
