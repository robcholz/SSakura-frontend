//
// Created by robcholz on 2/28/24.
//
#pragma once

#ifndef ANEMOS_OBJECTEXPRESSIONAST_HPP
#define ANEMOS_OBJECTEXPRESSIONAST_HPP

#include "ExpressionAST.hpp"
#include "anemos/type/ObjectReference.hpp"

namespace anemos {
class ObjectExpressionAST : public ExpressionAST {
 public:
  explicit ObjectExpressionAST(ObjectReference objectReference);

  void execute() override;

 private:
  ObjectReference objectReference;
};
}  // namespace anemos

#endif  // ANEMOS_OBJECTEXPRESSIONAST_HPP
