//
// Created by robcholz on 11/25/23.
//
#include <vector>

#include <spdlog/spdlog.h>

#include "Parser.hpp"
#include "BinaryOperator.hpp"
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
    this->currentToken = Lexer::Token{};
}

const Lexer* Parser::getLexer() const {
    return lexer;
}

const Lexer::Token& Parser::getNextToken() {
    currentToken = lexer->getToken();
    switch (lexer->getTokenCategory()) {
        case Lexer::TokenCategory::KEYWORD: spdlog::info(ssa::to_string(lexer->getKeyword()));
            break;
        case Lexer::TokenCategory::SYMBOL: spdlog::info(ssa::to_string(lexer->getSymbol()));
            break;
        case Lexer::TokenCategory::LITERAL: spdlog::info(lexer->getLiteralVal());
            break;
        case Lexer::TokenCategory::IDENTIFIER: spdlog::info(lexer->getIdentifierVal());
            break;
        case Lexer::TokenCategory::EOF_TERMINATOR: spdlog::info("_TERMINATE_");
            break;
    }
    return currentToken;
}

const Lexer::Token& Parser::getCurrentToken() const {
    return currentToken;
}

int Parser::getTokenPrecedence() const {
    const auto& token = getCurrentToken();
    return BinaryOperator::getPrecedence(token);
}

// numberExpr
// ::=number
std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
    auto result = std::make_unique<NumberExprAST>(lexer->getLiteralVal());
    getNextToken(); // eat number
    return std::move(result);
}

// parenthesisExpr
// ::=(expr)
std::unique_ptr<ExprAST> Parser::parseParenthesisExpr() {
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LPAREN);
    auto expr = parseExpr();
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RPAREN);
    return expr;
}

// identifierExpr
// ::=identifier
// ::=identifier(expr,expr,...)
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    auto identifier = lexer->getIdentifierVal();
    getNextToken(); // eat identifier
    if (!Checker::verifyCurrentToken(this,ssa::ReservedSymbol::LPAREN,true)) {
        return std::make_unique<VariableExprAST>(identifier);
    } // ::=identifier

    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LPAREN);
    // TODO
    std::vector<std::unique_ptr<ExprAST>> arguments;
    while (!Checker::verifyCurrentToken(this,ssa::ReservedSymbol::RPAREN,true)) {
        arguments.push_back(parseExpr());
        if (Checker::verifyCurrentToken(this,ssa::ReservedSymbol::RPAREN,true)) {
            break;
        } else {
            getNextToken();
        }
    }
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RPAREN);
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
    if (token.isSymbol() && token.getSymbol() == ssa::ReservedSymbol::LPAREN)
        return parseParenthesisExpr();
    if (token.isKeyword() && token.getKeyword() == ssa::Keyword::IF)
        return parseIfExpr();
    if (token.isKeyword() && token.getKeyword() == ssa::Keyword::RETURN)
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
        const ssa::BinaryOperator binaryOP = BinaryOperator::getOperator(getCurrentToken());
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
    std::string function_name = getCurrentToken().getIdentifier();
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LPAREN);
    auto param_list = parseParamListExpr();
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RPAREN);
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::COLON);
    const auto return_type_str = lexer->getIdentifierVal();
    getNextToken(); // <type>
    return std::make_unique<PrototypeAST>(function_name,
                                          std::move(param_list),
                                          Type(return_type_str)
    );
}

std::unique_ptr<PrototypeAST> Parser::parseExternExpr() {
    Checker::getNextVerifyThisToken(this, ssa::Keyword::EXTERN);
    return parsePrototypeExpr();
}

std::unique_ptr<FunctionAST> Parser::parseFunctionExpr() {
    Checker::getNextVerifyThisToken(this, ssa::Keyword::PROCEDURE);
    auto proto = parsePrototypeExpr();
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LBRACE);
    auto expr = parseExpr();
    Checker::getNextVerifyThisToken(this,ssa::ReservedSymbol::RBRACE);
    auto result = std::make_unique<FunctionAST>(std::move(proto), std::move(expr));
    return std::move(result);
}

std::unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
    if (auto e = parseExpr()) {
        auto proto = std::make_unique<PrototypeAST>(
            "",
            std::make_unique<ParameterList>(ParameterList::emptyParamList()),
            Type(ssa::Elementary::I32));
        return std::make_unique<FunctionAST>(
            std::move(proto),
            std::move(e)
        );
    }
    return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseIfExpr() {
    Checker::getNextVerifyThisToken(this, ssa::Keyword::IF); // eat if
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LPAREN);
    std::unique_ptr<ExprAST> condition = parseExpr();
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RPAREN);
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LBRACE);
    std::unique_ptr<ExprAST> then_expr = parseExpr(); // TODO ERROR OCCURED HERE
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RBRACE);
    if (Checker::verifyEatCurrentToken(this, ssa::Keyword::ELSE)) {
        Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LBRACE);
        std::unique_ptr<ExprAST> else_expr = parseExpr();
        Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RBRACE);
        return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr), std::move(else_expr));
    }
    return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr), nullptr);
}

std::unique_ptr<ExprAST> Parser::parseRepeatExpr() {
    Checker::getNextVerifyThisToken(this, ssa::Keyword::REPEAT);
    if (Checker::verifyEatCurrentToken(this, ssa::ReservedSymbol::LPAREN)) {
        auto condition_expr = parseExpr();
        Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RPAREN);
        Checker::getNextVerifyThisToken(this, ssa::Keyword::TIMES);
    } else if (Checker::verifyEatCurrentToken(this, ssa::Keyword::UNTIL)) {
        auto condition_expr = parseExpr();
    } else {
        // TODO SYNTAX ERROR
    }
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::LBRACE);
    auto body_expr = parseExpr();
    Checker::getNextVerifyThisToken(this, ssa::ReservedSymbol::RBRACE);
    return std::move(body_expr);
}

std::unique_ptr<ExprAST> Parser::parseReturnExpr() {
    Checker::getNextVerifyThisToken(this, ssa::Keyword::RETURN);
    auto returned_expr = parseExpr();
    return std::move(returned_expr);
}

// ::=name:type,name:type
std::unique_ptr<ParameterList> Parser::parseParamListExpr() {
    // TODO
    auto parm_list = std::make_unique<ParameterList>(ParameterList::emptyParamList());
    while (!Checker::verifyCurrentToken(this, ssa::ReservedSymbol::RPAREN,true)) {
        auto type = parseTypeNameExpr();
        parm_list->add(std::move(type));
        Checker::getNextVerifyNextToken(this,
            std::vector{ssa::ReservedSymbol::RPAREN, ssa::ReservedSymbol::COMMA});
    }
    return std::move(parm_list);
}

// ::=name:type
std::unique_ptr<VariableDefinition> Parser::parseTypeNameExpr() {
    getNextToken(); // <name>
    auto name = lexer->getIdentifierVal();
    Checker::getNextVerifyNextToken(this, ssa::ReservedSymbol::COLON);
    getNextToken(); // <type>
    const auto type_str = lexer->getIdentifierVal();
    return std::make_unique<VariableDefinition>(name, type_str);
}
