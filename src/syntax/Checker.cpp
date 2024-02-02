//
// Created by robcholz on 12/22/23.
//
#include "syntax/Checker.hpp"

using namespace ssa;

Checker& Checker::getInstance() {
  static Checker checker;
  return checker;
}

const Token& Checker::getNextVerifyThisToken(Parser* parser,
                                                    Keyword keyword) {
  return getNextVerifyThisToken<Keyword>(
      parser, ErrorUnexpectedKeyword, keyword);
}

const Token& Checker::getNextVerifyThisToken(
    Parser* parser,
    Symbol symbol) {
  return getNextVerifyThisToken<Symbol>(
      parser, ErrorUnexpectedSymbol, symbol);
}

const Token& Checker::getNextVerifyNextToken(Parser* parser,Keyword keyword) {
  return getNextVerifyNextToken<Keyword>(
      parser, ErrorUnexpectedKeyword, keyword);
}

const Token& Checker::getNextVerifyNextToken(
    Parser* parser,
    Symbol symbol) {
  return getNextVerifyNextToken<Symbol>(
      parser, ErrorUnexpectedSymbol, symbol);
}

const Token& Checker::getNextVerifyNextToken(
    Parser* parser,
    const std::vector<Symbol>& symbols) {
  return getNextVerifyNextToken<Symbol>(
      parser, ErrorUnexpectedSymbol, symbols);
}

bool Checker::verifyCurrentToken(const Parser* parser,
                                 Keyword keyword,
                                 bool silence) {
  return verifyCurrentToken<Keyword>(parser, ErrorUnexpectedKeyword,
                                               keyword, silence);
}

bool Checker::verifyCurrentToken(const Parser* parser,
                                 Symbol symbol,
                                 bool silence) {
  return verifyCurrentToken<Symbol>(
      parser, ErrorUnexpectedSymbol, symbol, silence);
}

bool Checker::verifyEatCurrentToken(Parser* parser, Keyword keyword) {
  if (verifyCurrentToken(parser, keyword)) {
    parser->getNextToken();
    return true;
  }
  return false;
}

bool Checker::verifyEatCurrentToken(Parser* parser,
                                    Symbol symbol) {
  if (verifyCurrentToken(parser, symbol)) {
    parser->getNextToken();
    return true;
  }
  return false;
}
