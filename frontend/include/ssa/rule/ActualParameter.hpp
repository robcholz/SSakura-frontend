//
// Created by robcholz on 2/28/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ACTUALPARAMETER_HPP
#define SSAKURA_FRONTEND_ACTUALPARAMETER_HPP

#include "FormalParameter.hpp"
#include "ssa/value/Value.hpp"

namespace ssa{
class ActualParameter {
 public:
  // TODO
  explicit ActualParameter(const std::string& name, Value value);
  explicit ActualParameter(Value value);

  FormalParameter toFormalParameter() const;

  const Value& getValue() const;
  const std::string& getName() const;

 private:
  Value value;
  std::string name;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_ACTUALPARAMETER_HPP
