//
// Created by robcholz on 2/28/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ACTUALPARAMETER_HPP
#define SSAKURA_FRONTEND_ACTUALPARAMETER_HPP

#include ""

namespace ssa{
class ActualParameter {
 public:
  explicit ActualParameter(const std::string& name, const Value& value);
  explicit ActualParameter(const Value& value);

  const Value& getValue() const;
  const std::string& getName() const;

 private:

};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_ACTUALPARAMETER_HPP
