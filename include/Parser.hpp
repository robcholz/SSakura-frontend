//
// Created by robcholz on 11/26/23.
//
#pragma once

#ifndef SSAKURA_PARSER_HPP
#define SSAKURA_PARSER_HPP


#include <memory>
#include <map>
#include "Lexer.hpp"
#include "ast/ExprAST.hpp"
#include "ast/FunctionAST.hpp"

class Parser {
public:
    explicit Parser(Lexer* lexer);
    int getNextToken();
    int getCurrentToken();
    std::unique_ptr<FunctionAST> parseFunctionExpr();
    std::unique_ptr<FunctionAST> parseTopLevelExpr();
private:
    int getTokenPrecedence();
    std::unique_ptr<ExprAST> parseNumberExpr();
    std::unique_ptr<ExprAST> parseParenthesisExpr();
    std::unique_ptr<ExprAST> parseIdentifierExpr();
    std::unique_ptr<ExprAST> parsePrimaryExpr();
    std::unique_ptr<ExprAST> parseBinaryOPRightExpr(int minPrecedence,std::unique_ptr<ExprAST> leftExpr);
    std::unique_ptr<ExprAST> parseExpr();

private:
    const std::map<char, int> binaryOPPrecedence = {
        {'<', 10}, {'+', 20}, {'-', 20}, {'*', 40}};

    Lexer* lexer;
    int currentToken;
};

#endif //SSAKURA_PARSER_HPP
