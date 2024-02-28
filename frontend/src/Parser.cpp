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

Parser::Parser(Lexer* lexer) {
  this->lexer = lexer;
  this->currentToken = Token{};
}

const Lexer* Parser::getLexer() const {
  return lexer;
}

const Token& Parser::getNextToken() {
  currentToken = lexer->getToken();
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
  auto number = lexer->getLiteralVal();
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
// ::=identifier(expr,expr,...)
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
  auto identifier = lexer->getIdentifierVal();
  getNextToken();  // eat identifier
  if (!Checker::verifyCurrentToken(this, Symbol::LPAREN, true)) {
    return std::make_unique<VariableExprAST>(identifier);
  }  // ::=identifier

  Checker::getNextVerifyThisToken(this, Symbol::LPAREN);
  // TODO
  std::vector<std::unique_ptr<ExprAST>> arguments;
  while (!Checker::verifyCurrentToken(this, Symbol::RPAREN, true)) {
    arguments.push_back(parseExpr());
    if (Checker::verifyCurrentToken(this, Symbol::RPAREN, true)) {
      break;
    } else {
      getNextToken();
    }
  }
  Checker::getNextVerifyThisToken(this, Symbol::RPAREN);
  return std::make_unique<CallableExprAST>(identifier, std::move(arguments));
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
  Checker::getNextVerifyThisToken(this, Symbol::LPAREN);
  auto param_list = parseParamListRule();
  Checker::getNextVerifyThisToken(this, Symbol::RPAREN);
  Checker::getNextVerifyThisToken(this, Symbol::COLON);
  auto return_type = parseTypeRule();
  getNextToken();  // <type>
  return std::make_unique<PrototypeAST>(function_name, std::move(param_list),
                                        std::move(return_type));
}

std::unique_ptr<PrototypeAST> Parser::parseExternExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::EXTERN);
  return parsePrototypeExpr();
}

std::unique_ptr<FunctionAST> Parser::parseFunctionExpr() {
  Checker::getNextVerifyThisToken(this, Keyword::PROCEDURE);
  auto proto = parsePrototypeExpr();
  auto expr = parseBraceExpr();
  auto result =
      std::make_unique<FunctionAST>(std::move(proto), std::move(expr));
  return std::move(result);
}

std::unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
  if (auto e = parseExpr()) {
    auto proto = std::make_unique<PrototypeAST>(
        "main",
        std::make_unique<ParameterList>(ParameterList::emptyParamList()),
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

// ::=name:type,name:type
std::unique_ptr<ParameterList> Parser::parseParamListRule() {
  // TODO
  auto parm_list =
      std::make_unique<ParameterList>(ParameterList::emptyParamList());
  while (!Checker::verifyCurrentToken(this, Symbol::RPAREN, true)) {
    auto type = parseTypeNameRule();
    parm_list->add(std::move(type));
    Checker::getNextVerifyNextToken(this,
                                    std::vector{Symbol::RPAREN, Symbol::COMMA});
  }
  return std::move(parm_list);
}

// ::=name:type
std::unique_ptr<VariableDeclaration> Parser::parseTypeNameRule() {
  getNextToken();  // <name>
  auto name = lexer->getIdentifierVal();
  Checker::getNextVerifyNextToken(this, Symbol::COLON);
  getNextToken();  // <type>
  std::unique_ptr<Type> type_str = parseTypeRule();
  return std::make_unique<VariableDeclaration>(name, Value(*type_str));
}

std::unique_ptr<Type> Parser::parseTypeRule() const {
  const auto& type_str = getCurrentToken().getIdentifier();
  const auto& maybe_primitive = ssa::from_string<Primitive>(type_str);
  std::unique_ptr<Type> type;
  if (maybe_primitive.has_value())
    type = std::make_unique<Type>(maybe_primitive.value());
  // TODO user-defined type
  return std::move(type);
}
