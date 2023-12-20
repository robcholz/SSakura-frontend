//
// Created by robcholz on 11/25/23.
//
#include <vector>


#include "Parser.hpp"
#include "ast/ProtoTypeAST.hpp"
#include "ast/FunctionAST.hpp"
#include "ast/BinaryExprAST.hpp"
#include "ast/CallableExprAST.hpp"
#include "ast/IfExprAST.hpp"
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
        case (int) Lexer::Token::IF:
            return parseIfExpr();
        case (int) Lexer::Token::RETURN:
            return parseReturnExpr();
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

// prototype
//   ::= id (param_list_ast)
std::unique_ptr<PrototypeAST> Parser::parsePrototypeExpr() {
    std::string function_name = lexer->getIdentifierVal();
    getNextToken(); // (
    auto param_list = parseParamListExpr();
    getNextToken(); // )
    getNextToken(); // :
    auto return_type_str=lexer->getIdentifierVal();
    getNextToken(); // <type>
    return std::make_unique<PrototypeAST>(function_name,
        std::move(param_list),
        Type(return_type_str)
        );
}

std::unique_ptr<PrototypeAST> Parser::parseExternExpr() {
    getNextToken();
    return parsePrototypeExpr();
}

std::unique_ptr<FunctionAST> Parser::parseFunctionExpr() {
    getNextToken(); // eat PRODCEDURE
    auto proto = parsePrototypeExpr();
    getNextToken(); // eat {
    auto expr = parseExpr();
    getNextToken(); // eat }
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
    getNextToken(); // eat if
    getNextToken(); // eat (
    std::unique_ptr<ExprAST> condition = parseExpr();
    getNextToken(); // eat )
    getNextToken(); // eat {
    std::unique_ptr<ExprAST> then_expr = parseExpr();
    getNextToken(); // eat }
    if (getCurrentToken() == (int) Lexer::Token::ELSE) {
        getNextToken(); // eat else
        getNextToken(); // eat {
        std::unique_ptr<ExprAST> else_expr = parseExpr();
        getNextToken(); // eat }
        return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr), std::move(else_expr));
    }
    return std::make_unique<IfExprAST>(std::move(condition), std::move(then_expr), nullptr);
}

std::unique_ptr<ExprAST> Parser::parseRepeatExpr() {
    getNextToken(); // eat REPEAT
    if (getCurrentToken() == '(') {
        getNextToken(); // eat (
        auto condition_expr = parseExpr();
        getNextToken(); // eat )
        getNextToken(); // eat TIMES
    } else if (getCurrentToken() == (int) Lexer::Token::UNTIL) {
        getNextToken(); // eat UNTIL
        auto condition_expr = parseExpr();
    } else {
        // TODO SYNTAX ERROR
    }
    getNextToken(); // eat {
    auto body_expr = parseExpr();
    getNextToken(); // eat }
    return std::move(body_expr);
}

std::unique_ptr<ExprAST> Parser::parseReturnExpr() {
    getNextToken(); // eat RETURN
    auto returned_expr = parseExpr();
    return std::move(returned_expr);
}

// ::=name:type,name:type,
// ::=name:type,name:type
std::unique_ptr<ParameterList> Parser::parseParamListExpr() {
    // TODO
    auto parm_list = std::make_unique<ParameterList>(ParameterList::emptyParamList());
    while (getCurrentToken() != ')') {
        auto type = parseTypeNameExpr();
        parm_list->add(std::move(type));
        getNextToken(); // ,
    }
    return std::move(parm_list);
}

// ::=name:type
std::unique_ptr<VariableDefinition> Parser::parseTypeNameExpr() {
    getNextToken(); // <name>
    auto name = lexer->getIdentifierVal();
    getNextToken(); // :
    getNextToken(); // <type>
    const auto type_str = lexer->getIdentifierVal();
    return std::make_unique<VariableDefinition>(name, type_str);
}
