//
// Created by robcholz on 11/28/23.
//
#pragma once

#ifndef SSAKURA_PROTOTYPEAST_HPP
#define SSAKURA_PROTOTYPEAST_HPP

#include <string>
#include <vector>
#include <memory>

#include "rule/ParameterList.hpp"
#include "type/Type.hpp"
#include "value/Function.hpp"

namespace ssa {
class PrototypeAST {
 public:
  PrototypeAST(const std::string& name,
               std::unique_ptr<ParameterList> arguments,
               std::unique_ptr<Type> returnType);

  std::string getName() const;

  const Type& getReturnType() const;

  Function codeGen();

 private:
  std::string name;
  std::unique_ptr<ParameterList> arguements;
  std::unique_ptr<Type> returnType;
};
}  // namespace ssa

#endif  // SSAKURA_PROTOTYPEAST_HPP
