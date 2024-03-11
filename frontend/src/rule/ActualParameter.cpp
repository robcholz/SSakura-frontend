//
// Created by robcholz on 3/10/24.
//
#include <algorithm>
#include <utility>

#include "ssa/rule/ActualParameter.hpp"

using namespace ssa;

void ActualParameter::add(std::unique_ptr<ExprAST> parameter) {
  parameters.push_back(std::move(parameter));
}

bool ActualParameter::canCastToFormalParameter(
    const FormalParameter& formalParameter) const {
  return false;
}
