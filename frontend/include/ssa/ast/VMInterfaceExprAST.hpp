//
// Created by robcholz on 3/11/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VMINTERFACEEXPRAST_HPP
#define SSAKURA_FRONTEND_VMINTERFACEEXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"
#include "ProtoTypeAST.hpp"

namespace ssa {
class VMInterfaceExprAST : public ExprAST {
 public:
  explicit VMInterfaceExprAST(std::unique_ptr<PrototypeAST> prototype);

  const PrototypeAST& getPrototype() const;

  ExprType getType() const final;
  //std::expected<ssa::Type, ExprType> hasReturnType() const final;

 private:
  std::unique_ptr<PrototypeAST> prototype;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_VMINTERFACEEXPRAST_HPP
