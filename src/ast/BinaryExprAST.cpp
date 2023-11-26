//
// Created by robcholz on 11/25/23.
//
#include "ast/BinaryExprAST.hpp"


BinaryExprAST::BinaryExprAST(char op, std::unique_ptr<ExprAST> leftExprAst, std::unique_ptr<ExprAST> rightExprAst) {
    this->op=op;
    this->leftExprAst=std::move(leftExprAst);
    this->rightExprAst=std::move(rightExprAst);
}

