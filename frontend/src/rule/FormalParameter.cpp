//
// Created by robcholz on 12/19/23.
//
#include "ssa/rule/FormalParameter.hpp"
#include <algorithm>

using namespace ssa;

bool FormalParameter::operator==(const FormalParameter& other) const {
  if (this->size() != other.size())
    return false;
  return std::equal(this->begin(), this->end(), other.begin(), other.end(),
                    [](const auto& a, const auto& b) { return *a == *b; });
}

void FormalParameter::add(std::unique_ptr<VariableDeclaration> type) {
  parameters.push_back(std::move(type));
}

size_t FormalParameter::size() const {
  return parameters.size();
}

FormalParameter FormalParameter::emptyParameter() {
  return FormalParameter{};
}
