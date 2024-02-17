//
// Created by robcholz on 11/26/23.
//
#pragma once

#ifndef SSAKURA_FUNCTIONAST_HPP
#define SSAKURA_FUNCTIONAST_HPP

#include <memory>
#include "value/Value.hpp"

namespace ssa {
class ExprAST;
class PrototypeAST;

class FunctionAST {
 public:
  explicit FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                       std::unique_ptr<ExprAST> body);
  Value codeGen();

 private:
  std::unique_ptr<PrototypeAST> prototype;
  std::unique_ptr<ExprAST> body;
};
}  // namespace ssa

#endif  // SSAKURA_FUNCTIONAST_HPP
