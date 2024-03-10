//
// Created by robcholz on 2/26/24.
//
#pragma once

#ifndef ANEMOS_VARIABLEDECLARATION_HPP
#define ANEMOS_VARIABLEDECLARATION_HPP

#include "Value.hpp"

namespace anemos {
class VariableDeclaration {
 public:
  explicit VariableDeclaration(std::string name, Type type);

 private:
  Type type;
  std::string name;
};
}  // namespace anemos

#endif  // ANEMOS_VARIABLEDECLARATION_HPP
