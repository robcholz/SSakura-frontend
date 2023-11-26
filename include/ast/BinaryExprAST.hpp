//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BINARYEXPRAST_HPP
#define SSAKURA_FRONTEND_BINARYEXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"


class BinaryExprAST : public ExprAST {
public:
    explicit BinaryExprAST(char op,std::unique_ptr<ExprAST> leftExprAst,std::unique_ptr<ExprAST> rightExprAst);
private:
    char op;
    std::unique_ptr<ExprAST> leftExprAst;
    std::unique_ptr<ExprAST> rightExprAst;
};

#endif //SSAKURA_FRONTEND_BINARYEXPRAST_HPP
