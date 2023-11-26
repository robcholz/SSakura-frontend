//
// Created by robcholz on 11/25/23.
//
#include <vector>
#include "Parser.hpp"
#include "ast/BinaryExprAST.hpp"
#include "ast/CallableExprAST.hpp"
#include "ast/NumberExprAST.hpp"
#include "ast/VariableExprAST.hpp"


Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->currentToken = -1;
}

int Parser::getNextToken() {
    return currentToken = lexer->getToken();
}

int Parser::getCurrentToken() {
    return currentToken;
}

int Parser::getTokenPrecedence() {
    auto token = static_cast<char>(getCurrentToken());
    if (binaryOPPrecedence.contains(token))
        return binaryOPPrecedence.at(token);
    return -1;
}

// numberExpr
// ::=number
std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
    auto result = std::make_unique<NumberExprAST>(lexer->getNumberVal());
    getNextToken();
    return std::move(result);
}

// parenthesisExpr
// ::=(expr)
std::unique_ptr<ExprAST> Parser::parseParenthesisExpr() {
    getNextToken(); // eat (
    auto expr = parseExpr();
    getNextToken(); // eat )
    return expr;
}

// identifierExpr
// ::=identifier
// ::=identifier(expr,expr,...)
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    auto identifier = lexer->getIdentifierVal();
    getNextToken();
    if (getCurrentToken() != '(') {
        return std::make_unique<VariableExprAST>(identifier);
    } // ::=identifier

    getNextToken(); // eat '('
    std::vector<std::unique_ptr<ExprAST>> arguments;
    while (getCurrentToken() != ')') {
        arguments.push_back(parseExpr());
        if (getCurrentToken() == ')') {
            break;
        } else {
            getNextToken();
        }
    }
    getNextToken(); // eat ')'
    return std::make_unique<CallableExprAST>(identifier, std::move(arguments));
}

// primaryExpr
// ::=identifierExpr
// ::=numberExpr
// ::=parenthesisExpr
std::unique_ptr<ExprAST> Parser::parsePrimaryExpr() {
    switch (getCurrentToken()) {
        case (int) Lexer::Token::IDENTIFIER:
            return parseIdentifierExpr();
        case (int) Lexer::Token::NUMBER:
            return parseNumberExpr();
        case '(':
            return parseParenthesisExpr();
        default:
            return nullptr;
    }
}

// leftExpr [binop primary] [binop primary] ...
std::unique_ptr<ExprAST> Parser::parseBinaryOPRightExpr(int minPrecedence, std::unique_ptr<ExprAST> leftExpr) {
    while (true) {
        const int current_precedence = getTokenPrecedence();
        if (current_precedence < minPrecedence) {
            return leftExpr;
        }
        int binaryOP = getCurrentToken();
        getNextToken(); // eat binop
        auto rightExpr = parsePrimaryExpr();
        const int next_precedence = getTokenPrecedence();
        if (current_precedence < next_precedence) {
            rightExpr = parseBinaryOPRightExpr(current_precedence + 1, std::move(rightExpr));
        }
        leftExpr = std::make_unique<BinaryExprAST>(binaryOP, std::move(leftExpr), std::move(rightExpr));
    }
}

// expr
// ::= primary [binop primary] [binop primary] ...
std::unique_ptr<ExprAST> Parser::parseExpr() {
    auto leftExpr = parsePrimaryExpr();
    return parseBinaryOPRightExpr(0, std::move(leftExpr));
}

std::unique_ptr<FunctionAST> Parser::parseFunctionExpr() {
    getNextToken(); // eat PRODCEDURE
    std::string function_name=lexer->getIdentifierVal();
    getNextToken();
    std::vector<std::string> arguement_names;
    while (getNextToken()==(int)Lexer::Token::IDENTIFIER) {
        arguement_names.push_back(lexer->getIdentifierVal());
    }
    getNextToken();
    auto expr=parseExpr();
    auto result=std::make_unique<FunctionAST>(function_name,std::move(arguement_names),std::move(expr));
    return std::move(result);
}

std::unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
    auto expr = parseExpr();
    return std::make_unique<FunctionAST>("",std::move(std::vector<std::string>()), std::move(expr));
}

