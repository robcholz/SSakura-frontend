//
// Created by robcholz on 11/26/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_PARSER_HPP
#define SSAKURA_FRONTEND_PARSER_HPP

#include <functional>
#include <memory>

#include "Lexer.hpp"

#include "ssa/ast/BlockExprAST.hpp"
#include "ssa/ast/ExprAST.hpp"
#include "ssa/ast/FunctionAST.hpp"
#include "ssa/ast/ProtoTypeAST.hpp"

#include "ssa/rule/FormalParameter.hpp"
#include "ssa/rule/VariableDeclaration.hpp"

namespace ssa {
class Parser {
 public:
  explicit Parser(Lexer& lexer);
  const Lexer& getLexer() const;

  const Token& getNextToken();
  const Token& getCurrentToken() const;

  std::unique_ptr<PrototypeAST> parsePrototypeExpr();
  std::unique_ptr<PrototypeAST> parseExternExpr();
  std::unique_ptr<FunctionAST> parseFunctionExpr();
  std::unique_ptr<FunctionAST> parseTopLevelExpr();

 private:
  std::reference_wrapper<Lexer> lexer;
  Token currentToken;

  int getTokenPrecedence() const;

  // expressions
  std::unique_ptr<ExprAST> parseNumberExpr();
  std::unique_ptr<ExprAST> parseParenthesisExpr();
  std::unique_ptr<ExprAST> parseBraceExpr();
  std::unique_ptr<ExprAST> parseIdentifierExpr();
  std::unique_ptr<ExprAST> parseCallableExpr();
  std::unique_ptr<ExprAST> parseBinaryOPRightExpr(
      int minPrecedence,
      std::unique_ptr<ExprAST> leftExpr);
  std::unique_ptr<ExprAST> parseExpr();
  std::unique_ptr<ExprAST> parseIfExpr();
  std::unique_ptr<ExprAST> parseRepeatExpr();
  std::unique_ptr<ExprAST> parseReturnExpr();
  std::unique_ptr<ExprAST> parsePrimaryExpr();
  std::unique_ptr<ExprAST> parseBlockExpr();
  std::unique_ptr<ExprAST> parseAssignmentExpr();
  std::unique_ptr<ExprAST> parseDeclarationExpr();
  std::unique_ptr<ExprAST> parseMixedDeclarationDefinitionExpr();

  std::unique_ptr<FormalParameter> parseFormalParameterRule();
  std::unique_ptr<VariableDeclaration> parseTypeNameRule();
  std::unique_ptr<Type> parseTypeRule() const;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_PARSER_HPP
