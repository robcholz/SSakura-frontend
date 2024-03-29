//
// Created by robcholz on 11/25/23.
//
#include <vector>

#include "ssa/Parser.hpp"
#include "ssa/ast/BinaryExprAST.hpp"
#include "ssa/ast/CallableExprAST.hpp"
#include "ssa/ast/FunctionAST.hpp"
#include "ssa/ast/IfExprAST.hpp"
#include "ssa/ast/NumberExprAST.hpp"
#include "ssa/ast/ProtoTypeAST.hpp"
#include "ssa/ast/VariableExprAST.hpp"
#include "ssa/lang/BinaryOperator.hpp"
#include "ssa/syntax/Checker.hpp"

using namespace ssa;

Parser::Parser(Lexer& lexer) : lexer(std::ref(lexer)), currentToken({}) {}

const Lexer& Parser::getLexer() const {
  return lexer;
}

const Token& Parser::getNextToken() {
  currentToken = lexer.get().getToken();
  return currentToken;
}

const Token& Parser::getCurrentToken() const {
  return currentToken;
}

int Parser::getTokenPrecedence() const {
  const auto& token = getCurrentToken();
  return BinaryOperator::getPrecedence(token);
}

// numberExpr
// ::=number
std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
  auto number = getCurrentToken().getLiteral();
  std::unique_ptr<NumberExprAST> result;

  if (number.find('.') != std::string::npos ||
      number.find('e') != std::string::npos ||
      number.find('E') != std::string::npos) {
    s_f64_t f_val = std::stod(number);
    result = std::make_unique<NumberExprAST>(f_val);
  } else {
    if (number.front() == '-') {
      s_i64_t i_val = std::stoll(number);
      result = std::make_unique<NumberExprAST>(i_val);
    } else {
      s_u64_t u_val = std::stoull(number);
      result = std::make_unique<NumberExprAST>(u_val);
    }
  }
  getNextToken();  // eat number
  return std::move(result);
}

// parenthesisExpr
// ::=(expr)
std::unique_ptr<ExprAST> Parser::parseParenthesisExpr() {
  Checker::getNextVerifyThisToken(this, Symbol::LPAREN);
  auto expr = parseExpr();
  Checker::getNextVerifyThisToken(this, Symbol::RPAREN);
  return expr;
}

/// braceExpr
/// ::={expr}
std::unique_ptr<ExprAST> Parser::parseBraceExpr() {
  Checker::getNextVerifyThisToken(this, Symbol::LBRACE);
  auto expr = parseExpr();
  Checker::getNextVerifyThisToken(this, Symbol::RBRACE);
  return expr;
}

// identifierExpr
// ::=identifier
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
  if (lexer.get().lookAhead().isSymbol() &&
      lexer.get().lookAhead().getSymbol() != Symbol::LPAREN) {
    auto identifier = getCurrentToken().getIdentifier();
    getNextToken();  // eat identifier
    return std::make_unique<VariableExprAST>(identifier);
  }  // ::=identifier

  return parseCallableExpr();
}

// ::=identifier(expr,expr,...)
std::unique_ptr<ExprAST> Parser::parseCallableExpr() {
  auto identifier = getCurrentToken().getIdentifier();
  getNextToken();  // eat identifier
  Checker::getNextVerifyThisToken(this, Symbol::LPAREN);
  auto parameter = parseActualParameterRule();
  Checker::getNextVerifyThisToken(this, Symbol::RPAREN);
  return std::make_unique<CallableExprAST>(identifier, std::move(parameter));
}

/// primaryExpr
/// ::=identifierExpr
/// ::=numberExpr
/// ::=parenthesisExpr
std::unique_ptr<ExprAST> Parser::parsePrimaryExpr() {
  const auto token = getCurrentToken();
  if (token.isIdentifier())
    return parseIdentifierExpr();
  if (token.isLiteral())
    return parseNumberExpr();
  if (token.isSymbol() && token.getSymbol() == Symbol::LPAREN)
    return parseParenthesisExpr();
  if (token.isKeyword() && token.getKeyword() == Keyword::IF)
    return parseIfExpr();
  if (token.isKeyword() && token.getKeyword() == Keyword::RETURN)
    return parseReturnExpr();
  return nullptr;
}

// leftExpr [binop primary] [binop primary] ...
std::unique_ptr<ExprAST> Parser::parseBinaryOPRightExpr(
    int minPrecedence,
    std::unique_ptr<ExprAST> leftExpr) {
  while (true) {
    const int current_precedence = getTokenPrecedence();
    if (current_precedence < minPrecedence) {
      return leftExpr;
    }
    const BinaryOperator::BinaryOperatorEnum binaryOP =
        BinaryOperator::getOperator(getCurrentToken());
    getNextToken();  // eat binop
    auto rightExpr = parsePrimaryExpr();
    const int next_precedence = getTokenPrecedence();
    if (current_precedence < next_precedence) {
      rightExpr =
          parseBinaryOPRightExpr(current_precedence + 1, std::move(rightExpr));
    }
    leftExpr = std::make_unique<BinaryExprAST>(binaryOP, std::move(leftExpr),
                                               std::move(rightExpr));
  }
}

// expr
// ::= primary [binop primary] [binop primary] ...
std::unique_ptr<ExprAST> Parser::parseExpr() {
  auto leftExpr = parsePrimaryExpr();
  return parseBinaryOPRightExpr(0, std::move(leftExpr));
}

// prototype
//   ::= id (param_list_ast)
std::unique_ptr<PrototypeAST> Parser::parsePrototypeExpr() {
  std::string function_name = getCurrentToken().getIdentifier();
  getNextToken(); // eat function_name
  Checker::getNextVerifyThisToken(this, Symbol::LPAREN);
  auto formal_parameter = parseFormalParameterRule();
  Checker::getNextVerifyThisToken(this, Symbol::RPAREN);
  auto return_type = parseTypeRule();
  return std::make_unique<PrototypeAST>(
      function_name, std::move(formal_parameter), std::move(return_type));
}

std::pair<std::unique_ptr<PrototypeAST>, std::unique_ptr<ExprAST>>
Parser::parseFunctionLikeExpr() {
  auto prototype = parsePrototypeExpr();
  auto expr = parseBraceExpr();
  return {std::move(prototype), std::move(expr)};
}

std::unique_ptr<VMInterfaceExprAST> Parser::parseExternExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::EXTERN);
  auto prototype = parsePrototypeExpr();
  return std::make_unique<VMInterfaceExprAST>(std::move(prototype));
}

std::unique_ptr<FunctionAST> Parser::parseFunctionExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::PROCEDURE);
  auto function_pair = parseFunctionLikeExpr();
  return std::make_unique<FunctionAST>(std::move(function_pair.first),
                                       std::move(function_pair.second));
}

std::unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
  if (auto e = parseExpr()) {
    auto proto = std::make_unique<PrototypeAST>(
        "main", std::make_unique<FormalParameter>(),
        std::make_unique<Type>(Primitive::I32));
    return std::make_unique<FunctionAST>(std::move(proto), std::move(e));
  }
  return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseIfExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::IF);  // eat if
  auto condition = parseParenthesisExpr();
  std::unique_ptr<ExprAST> then_expr = parseBraceExpr();
  if (Checker::verifyCurrentToken(this, Keyword::ELSE, true)) {
    Checker::getNextVerifyThisToken(this, Keyword::ELSE);
    auto else_expr = parseBraceExpr();
    return std::make_unique<IfExprAST>(
        std::move(condition), std::move(then_expr), std::move(else_expr));
  }
  return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr),
                                     nullptr);
}

std::unique_ptr<ExprAST> Parser::parseRepeatExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::REPEAT);
  if (Checker::verifyCurrentToken(this, Symbol::LPAREN)) {
    auto condition_expr = parseParenthesisExpr();
    Checker::getNextVerifyThisToken(this, Keyword::TIMES);
  } else if (Checker::verifyEatCurrentToken(this, Keyword::UNTIL)) {
    auto condition_expr = parseExpr();
  } else {
    // TODO SYNTAX ERROR
  }
  auto body_expr = parseBraceExpr();
  return std::move(body_expr);
}

std::unique_ptr<ExprAST> Parser::parseReturnExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::RETURN);
  auto returned_expr = parseExpr();
  return std::move(returned_expr);
}

// ::=_typeNameRule_,_typeNameRule_
std::unique_ptr<FormalParameter> Parser::parseFormalParameterRule() {
  auto parm_list = std::make_unique<FormalParameter>();
  if (lexer.get().lookAhead().isSymbol() &&
      lexer.get().lookAhead().getSymbol() == Symbol::RPAREN) {
    Checker::getNextVerifyNextToken(this, Symbol::RPAREN);
    return parm_list;
  }
  while (!Checker::verifyCurrentToken(this, Symbol::RPAREN, true)) {
    auto type = parseTypeNameRule();
    parm_list->add(std::move(type));
    if(Checker::verifyCurrentToken(this,Symbol::COMMA,true)){
      getNextToken();
    }
  }
  return std::move(parm_list);
}

std::unique_ptr<ActualParameter> Parser::parseActualParameterRule() {
  auto parameter = std::make_unique<ActualParameter>();
  auto tk = lexer.get().getToken();
  if (tk.isSymbol() && tk.getSymbol() == Symbol::RPAREN) {
    return parameter;
  }
  while (!Checker::verifyCurrentToken(this, Symbol::RPAREN, true)) {
    auto expr = parseExpr();
    parameter->add(std::move(expr));
    if (Checker::verifyCurrentToken(this, Symbol::COMMA, true)) {
      getNextToken();
    } else if (Checker::verifyCurrentToken(this, Symbol::RPAREN, true)) {
      return std::move(parameter);
    } else {
      // TODO SYNTAX ERROR
    }
  }
  return std::move(parameter);
}

// typeNameRule:=name+_typeRule_
std::unique_ptr<VariableDeclaration> Parser::parseTypeNameRule() {
  auto name = getCurrentToken().getIdentifier();
  getNextToken(); // eat name
  auto type_str = parseTypeRule();
  return std::make_unique<VariableDeclaration>(name, *type_str);
}

// typeRule=:{type}
std::unique_ptr<Type> Parser::parseTypeRule() {
  if (!(getCurrentToken().isSymbol() && getCurrentToken().getSymbol() == Symbol::COLON)) {
    return std::make_unique<Type>(Primitive::VOID);
  }
  getNextToken();
  const auto& type_str = getCurrentToken().getIdentifier();
  const auto& maybe_primitive = ssa::from_string<Primitive>(type_str);
  std::unique_ptr<Type> type;
  if (maybe_primitive.has_value())
    type = std::make_unique<Type>(maybe_primitive.value());
  // TODO user-defined type
  getNextToken();
  return std::move(type);
}
