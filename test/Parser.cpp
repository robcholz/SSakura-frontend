//
// Created by robcholz on 11/26/23.
//
#include <iostream>

#include <catch2/catch_all.hpp>

#include "Info.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "lang/Lang.hpp"

int main() {
  ssa::Lang::init();
  ssa::Lexer lexer;
  lexer.readFile(
      "/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/test/"
      "parserExample.txt");
  auto parser = ssa::Parser(&lexer);
  parser.getNextToken();
  bool flag = true;
  while (flag) {
    auto token = parser.getCurrentToken();
    if (token.isEOF()) {
      flag = false;
    } else if (token.isKeyword() &&
               token.getKeyword() == ssa::Keyword::EXTERN) {
      auto function = parser.parseExternExpr();
      std::cout << ("parsed a function declaration") << std::endl;
    } else if (token.isKeyword() &&
               token.getKeyword() == ssa::Keyword::PROCEDURE) {
      auto function = parser.parseFunctionExpr();
      std::cout << ("parsed a function definition") << std::endl;
    } else {
      auto function = parser.parseTopLevelExpr();
      std::cout << ("parsed a top level expr") << std::endl;
    }
  }
  std::error_code EC;
  return 0;
}
