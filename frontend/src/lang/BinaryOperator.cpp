//
// Created by robcholz on 2/1/24.
//
#include "ssa/lang/BinaryOperator.hpp"

using namespace ssa;

BinaryOperator::BinaryOperatorEnum BinaryOperator::getOperator(const Token& token) {
  if (token.isSymbol()) {
    const auto& symbol = token.getSymbol();
    if (symbol == Symbol::LABRAC)
      return BinaryOperator::LESS;
    if (symbol == Symbol::RABRAC)
      return BinaryOperator::GREATER;
    if (symbol == Symbol::PLUS)
      return BinaryOperator::ADD;
    if (symbol == Symbol::HYPHEN)
      return BinaryOperator::SUBTRACT;
    if (symbol == Symbol::ASTERISK)
      return BinaryOperator::MULTIPLE;
    if (symbol == Symbol::SLASH)
      return BinaryOperator::DIVISION;
    if (symbol == Symbol::EQUAL_SIGN)
      return BinaryOperator::EQUAL;
  }
  if (token.isKeyword()) {
    const auto& identifier = token.getKeyword();
    if (identifier == Keyword::MOD)
      return BinaryOperator::MOD;
    if (identifier == Keyword::AND)
      return BinaryOperator::AND;
    if (identifier == Keyword::NOT)
      return BinaryOperator::NOT;
    if (identifier == Keyword::OR)
      return BinaryOperator::OR;
  }
  return static_cast<BinaryOperatorEnum>(-1);
}

int BinaryOperator::getPrecedence(const Token& token) {
  return getPrecedence(getOperator(token));
}

int BinaryOperator::getPrecedence(BinaryOperator::BinaryOperatorEnum binaryOperator) {
  switch (binaryOperator) {
    case BinaryOperator::LESS:
      return 10;
    case BinaryOperator::GREATER:
      return 10;
    case BinaryOperator::ADD:
      return 20;
    case BinaryOperator::SUBTRACT:
      return 20;
    case BinaryOperator::MULTIPLE:
      return 30;
    case BinaryOperator::DIVISION:
      return 30;
    case BinaryOperator::MOD:
      return 30;
    case BinaryOperator::AND:
      return 40;
    case BinaryOperator::EQUAL:
      return 40;
    case BinaryOperator::NOT:
      return 40;
    case BinaryOperator::OR:
      return 40;
  }
  return -1;
}

