//
// Created by robcholz on 11/26/23.
//
#include <fmt/core.h>
#include <iostream>

#include <catch2/catch_all.hpp>

#include "ssa/Lexer.hpp"
#include "ssa/Parser.hpp"
#include "ssa/lang/Lang.hpp"

#include "Capability.hpp"
#include "anemos/registry/FunctionRegistry.hpp"
#include "anemos/type/Parameter.hpp"

int main() {
  auto& func_registry = anemos::FunctionRegistry::getInstance();
  ssa::Lang::init();
  ssa::Lexer lexer;
  lexer.readFile(
      "/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/"
      "ssakura_lang/test/"
      "parserExample.txt");
  auto parser = std::make_unique<ssa::Parser>(&lexer);
  parser->getNextToken();
  bool flag = true;
  while (flag) {
    auto token = parser->getCurrentToken();
    if (token.isEOF()) {
      flag = false;
    } else if (token.isKeyword() &&
               token.getKeyword() == ssa::Keyword::EXTERN) {
      auto function = parser->parseExternExpr();
      std::cout << ("parsed a function declaration") << std::endl;
    } else if (token.isKeyword() &&
               token.getKeyword() == ssa::Keyword::PROCEDURE) {
      auto function = parser->parseFunctionExpr();
      auto final_ast = ast_visitor(function.get());

      /// add func ast to registry
      func_registry.add(std::unique_ptr<anemos::FunctionExpressionAST>(
          dynamic_cast<anemos::FunctionExpressionAST*>(final_ast.release())));

      std::cout << ("parsed a function definition") << std::endl;
    } else {
      auto function = parser->parseTopLevelExpr();
      std::cout << ("parsed a top level expr") << std::endl;
    }
  }
  auto param=anemos::Parameter(
      anemos::VariableDeclaration("a", anemos::Value::makeF32(0.f))

      );
  func_registry.invoke("main", std::move(param));
  std::error_code EC;
  return 0;
}
