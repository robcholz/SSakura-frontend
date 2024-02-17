//
// Created by robcholz on 11/25/23.
//
#include "ast/BinaryExprAST.hpp"
#include "Info.hpp"
#include "adapter/ArithmeticOperationAdapter.hpp"
#include "type/Type.hpp"

using namespace ssa;

BinaryExprAST::BinaryExprAST(BinaryOperator::BinaryOperatorEnum op,
                             std::unique_ptr<ExprAST> leftExprAst,
                             std::unique_ptr<ExprAST> rightExprAst) {
  this->op = op;
  this->leftExprAst = std::move(leftExprAst);
  this->rightExprAst = std::move(rightExprAst);
}

Value BinaryExprAST::codeGen() {
  const auto leftAst = leftExprAst->codeGen();
  const auto rightAst = rightExprAst->codeGen();
  switch (this->op) {
    case BinaryOperator::ADD:
      return add(leftAst, rightAst);
    case BinaryOperator::SUBTRACT:
      return subtract(leftAst, rightAst);
    case BinaryOperator::MULTIPLE:
      return multiple(leftAst, rightAst);
    case BinaryOperator::DIVISION:
      return division(leftAst, rightAst);
    case BinaryOperator::MOD:
      return modulus(leftAst, rightAst);
    case BinaryOperator::LESS:
      return lessThan(leftAst, rightAst);
    case BinaryOperator::GREATER:
      return greaterThan(leftAst, rightAst);
    case BinaryOperator::EQUAL:
      return equality(leftAst, rightAst);
    case BinaryOperator::AND:
      return boolAnd(leftAst, rightAst);
    case BinaryOperator::OR:
      return boolOr(leftAst, rightAst);
    case BinaryOperator::NOT:
      return boolNot(rightAst);
  }
}

Value BinaryExprAST::equality(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::equalityGen(left, right);
}

Value BinaryExprAST::greaterThan(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::greaterThanGen(left, right);
}

Value BinaryExprAST::lessThan(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::lessThanGen(left, right);
}

Value BinaryExprAST::boolAnd(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::boolAndGen(left, right);
}

Value BinaryExprAST::boolOr(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::boolOrGen(left, right);
}

Value BinaryExprAST::boolNot(const Value& value) {
  return ArithmeticOperationAdapter::boolNotGen(value);
}

Value BinaryExprAST::modulus(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::modulusGen(left, right);
}

Value BinaryExprAST::add(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::addGen(left, right);
}

Value BinaryExprAST::subtract(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::subtractGen(left, right);
}

Value BinaryExprAST::multiple(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::multipleGen(left, right);
}

Value BinaryExprAST::division(const Value& left, const Value& right) {
  return ArithmeticOperationAdapter::divisionGen(left, right);
}
