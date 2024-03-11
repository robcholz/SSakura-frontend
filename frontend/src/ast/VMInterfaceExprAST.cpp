//
// Created by robcholz on 3/11/24.
//
#include "ssa/ast/VMInterfaceExprAST.hpp"

using namespace ssa;

VMInterfaceExprAST::VMInterfaceExprAST(std::unique_ptr<PrototypeAST> prototype) {
  this->prototype=std::move(prototype);
}

const PrototypeAST& VMInterfaceExprAST::getPrototype() const {
  return *prototype;
}

ExprAST::ExprType VMInterfaceExprAST::getType() const {
  return ExprAST::ExprType::VMINTERFACE_EXPR;
}
