//
// Created by robcholz on 11/26/23.
//
#pragma once

#ifndef SSAKURA_FUNCTIONAST_HPP
#define SSAKURA_FUNCTIONAST_HPP

#include <memory>
#include "ssa/ast/BlockExprAST.hpp"
#include "ssa/ast/ExprAST.hpp"
#include "ssa/ast/ProtoTypeAST.hpp"
#include "ssa/value/Value.hpp"

namespace ssa {
class FunctionAST : public ExprAST {
 public:
  explicit FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                       std::unique_ptr<BlockExprAST> body);
  explicit FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                       std::unique_ptr<ExprAST> body);
  const PrototypeAST& getPrototype() const;
  const BlockExprAST& getBody() const;

  Value codeGen() final;
  ExprAST::Type getType() const final;

 private:
  std::unique_ptr<PrototypeAST> prototype;
  std::unique_ptr<BlockExprAST> body;
};
}  // namespace ssa

#endif  // SSAKURA_FUNCTIONAST_HPP
