//
// Created by robcholz on 11/26/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_PARSER_HPP
#define SSAKURA_FRONTEND_PARSER_HPP

#include <memory>

#include "Lexer.hpp"
#include "ast/ExprAST.hpp"
#include "ast/ProtoTypeAST.hpp"
#include "ast/FunctionAST.hpp"
#include "rule/ParameterList.hpp"
#include "type/VariableDefinition.hpp"


class Parser {
public:
    explicit Parser(Lexer* lexer);
    const Lexer* getLexer() const;

    const Lexer::Token& getNextToken();
    const Lexer::Token& getCurrentToken()const;

    std::unique_ptr<PrototypeAST> parsePrototypeExpr();
    std::unique_ptr<PrototypeAST> parseExternExpr();
    std::unique_ptr<FunctionAST> parseFunctionExpr();
    std::unique_ptr<FunctionAST> parseTopLevelExpr();
private:
    Lexer* lexer;
    Lexer::Token currentToken;

    int getTokenPrecedence()const;
    std::unique_ptr<ExprAST> parseNumberExpr();
    std::unique_ptr<ExprAST> parseParenthesisExpr();
    std::unique_ptr<ExprAST> parseIdentifierExpr();
    std::unique_ptr<ExprAST> parseBinaryOPRightExpr(int minPrecedence,std::unique_ptr<ExprAST> leftExpr);
    std::unique_ptr<ExprAST> parseExpr();
    std::unique_ptr<ExprAST> parseIfExpr();
    std::unique_ptr<ExprAST> parseRepeatExpr();
    std::unique_ptr<ExprAST> parseReturnExpr();
    std::unique_ptr<ExprAST> parsePrimaryExpr();
    std::unique_ptr<ParameterList> parseParamListExpr();
    std::unique_ptr<VariableDefinition> parseTypeNameExpr();
};

#endif //SSAKURA_FRONTEND_PARSER_HPP
