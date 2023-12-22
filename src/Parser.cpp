//
// Created by robcholz on 11/25/23.
//
#include <vector>

#include <spdlog/spdlog.h>

#include "Parser.hpp"
#include "ast/ProtoTypeAST.hpp"
#include "ast/FunctionAST.hpp"
#include "ast/BinaryExprAST.hpp"
#include "ast/CallableExprAST.hpp"
#include "ast/IfExprAST.hpp"
#include "ast/NumberExprAST.hpp"
#include "ast/VariableExprAST.hpp"
#include "syntax/Checker.hpp"


Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->currentToken = "";
}

const Lexer* Parser::getLexer() const {
    return lexer;
}

std::string Parser::getNextToken() {
    currentToken = lexer->getToken();
    return currentToken;
}

std::string Parser::getCurrentToken() {
    return currentToken;
}

int Parser::getTokenPrecedence() {
    const auto token = getCurrentToken();
    if (binaryOPPrecedence.contains(token))
        return binaryOPPrecedence.at(token);
    return -1;
}

// numberExpr
// ::=number
std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
    auto result = std::make_unique<NumberExprAST>(lexer->getNumberVal());
    getNextToken(); // eat number
    return std::move(result);
}

// parenthesisExpr
// ::=(expr)
std::unique_ptr<ExprAST> Parser::parseParenthesisExpr() {
    Checker::getNextVerifyThisToken(this, "(");
    auto expr = parseExpr();
    Checker::getNextVerifyThisToken(this, ")");
    return expr;
}

// identifierExpr
// ::=identifier
// ::=identifier(expr,expr,...)
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    auto identifier = lexer->getIdentifierVal();
    getNextToken();
    if (getCurrentToken() != "(") {
        return std::make_unique<VariableExprAST>(identifier);
    } // ::=identifier

    Checker::getNextVerifyThisToken(this, "(");
    std::vector<std::unique_ptr<ExprAST>> arguments;
    while (getCurrentToken() != ")") {
        arguments.push_back(parseExpr());
        if (getCurrentToken() == ")") {
            break;
        } else {
            getNextToken();
        }
    }
    Checker::getNextVerifyThisToken(this, ")");
    return std::make_unique<CallableExprAST>(identifier, std::move(arguments));
}

/// primaryExpr
/// ::=identifierExpr
/// ::=numberExpr
/// ::=parenthesisExpr
std::unique_ptr<ExprAST> Parser::parsePrimaryExpr() {
    const auto var_view = getCurrentToken();
    if(var_view=="IDENTIFIER")
        return parseIdentifierExpr();
    if(var_view=="NUMBER")
        return parseNumberExpr();
    if(var_view=="(")
        return parseParenthesisExpr();
    if(var_view=="IF")
        return parseIfExpr();
    if(var_view=="RETURN")
        return parseReturnExpr();
    return nullptr;
}

// leftExpr [binop primary] [binop primary] ...
std::unique_ptr<ExprAST> Parser::parseBinaryOPRightExpr(int minPrecedence, std::unique_ptr<ExprAST> leftExpr) {
    while (true) {
        const int current_precedence = getTokenPrecedence();
        if (current_precedence < minPrecedence) {
            return leftExpr;
        }
        const auto binaryOP = getCurrentToken();
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

// prototype
//   ::= id (param_list_ast)
std::unique_ptr<PrototypeAST> Parser::parsePrototypeExpr() {
    std::string function_name = lexer->getIdentifierVal();
    Checker::getNextVerifyNextToken(this, "(");
    auto param_list = parseParamListExpr();
    Checker::getNextVerifyThisToken(this, ")");
    Checker::getNextVerifyThisToken(this, ":");
    const auto return_type_str = lexer->getIdentifierVal();
    getNextToken(); // <type>
    return std::make_unique<PrototypeAST>(function_name,
                                          std::move(param_list),
                                          Type(return_type_str)
    );
}

std::unique_ptr<PrototypeAST> Parser::parseExternExpr() {
    Checker::getNextVerifyThisToken(this, Lexer::Token::EXTERN);
    return parsePrototypeExpr();
}

std::unique_ptr<FunctionAST> Parser::parseFunctionExpr() {
    Checker::getNextVerifyThisToken(this, Lexer::Token::PROCEDURE);
    auto proto = parsePrototypeExpr();
    Checker::getNextVerifyThisToken(this, "{");
    auto expr = parseExpr();
    Checker::getNextVerifyThisToken(this, "}");
    auto result = std::make_unique<FunctionAST>(std::move(proto), std::move(expr));
    return std::move(result);
}

std::unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
    if (auto e = parseExpr()) {
        auto proto = std::make_unique<PrototypeAST>(
            "",
            std::make_unique<ParameterList>(ParameterList::emptyParamList()),
            Type(ElementaryType::I32));
        return std::make_unique<FunctionAST>(
            std::move(proto),
            std::move(e)
        );
    }
    return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseIfExpr() {
    Checker::getNextVerifyThisToken(this, Lexer::Token::IF); // eat if
    Checker::getNextVerifyThisToken(this, "(");
    std::unique_ptr<ExprAST> condition = parseExpr();
    Checker::getNextVerifyThisToken(this, ")");
    Checker::getNextVerifyThisToken(this, "{");
    std::unique_ptr<ExprAST> then_expr = parseExpr(); // TODO ERROR OCCURED HERE
    Checker::getNextVerifyThisToken(this, "}");
    if (Checker::promiseEatCurrentToken(this, Lexer::Token::ELSE)) {
        Checker::getNextVerifyThisToken(this, "{");
        std::unique_ptr<ExprAST> else_expr = parseExpr();
        Checker::getNextVerifyThisToken(this, "}");
        return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr), std::move(else_expr));
    }
    return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr), nullptr);
}

std::unique_ptr<ExprAST> Parser::parseRepeatExpr() {
    Checker::getNextVerifyThisToken(this, Lexer::Token::REPEAT);
    if (Checker::promiseEatCurrentToken(this, "(")) {
        auto condition_expr = parseExpr();
        Checker::getNextVerifyThisToken(this, ")");
        Checker::getNextVerifyThisToken(this, Lexer::Token::TIMES);
    } else if (Checker::promiseEatCurrentToken(this, Lexer::Token::UNTIL)) {
        auto condition_expr = parseExpr();
    } else {
        // TODO SYNTAX ERROR
    }
    Checker::getNextVerifyThisToken(this, "{");
    auto body_expr = parseExpr();
    Checker::getNextVerifyThisToken(this, "}");
    return std::move(body_expr);
}

std::unique_ptr<ExprAST> Parser::parseReturnExpr() {
    Checker::getNextVerifyThisToken(this, Lexer::Token::RETURN);
    auto returned_expr = parseExpr();
    return std::move(returned_expr);
}

// ::=name:type,name:type
std::unique_ptr<ParameterList> Parser::parseParamListExpr() {
    // TODO
    auto parm_list = std::make_unique<ParameterList>(ParameterList::emptyParamList());
    while (getCurrentToken() != ")") {
        auto type = parseTypeNameExpr();
        parm_list->add(std::move(type));
        Checker::getNextVerifyNextToken(this, std::vector<std::string_view>{")", ","});
    }
    return std::move(parm_list);
}

// ::=name:type
std::unique_ptr<VariableDefinition> Parser::parseTypeNameExpr() {
    getNextToken(); // <name>
    auto name = lexer->getIdentifierVal();
    Checker::getNextVerifyNextToken(this, ":");
    getNextToken(); // <type>
    const auto type_str = lexer->getIdentifierVal();
    return std::make_unique<VariableDefinition>(name, type_str);
}
