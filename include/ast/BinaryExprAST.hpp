//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BINARYEXPRAST_HPP
#define SSAKURA_FRONTEND_BINARYEXPRAST_HPP

#include <memory>
#include "ExprAST.hpp"
#include "ReservedWords.hpp"


class BinaryExprAST : public ExprAST {
public:
    explicit BinaryExprAST(ssa::BinaryOperator op,std::unique_ptr<ExprAST> leftExprAst,std::unique_ptr<ExprAST> rightExprAst);
    llvm::Value* codeGen() final;
private:
    ssa::BinaryOperator op;
    std::unique_ptr<ExprAST> leftExprAst;
    std::unique_ptr<ExprAST> rightExprAst;
};

#endif //SSAKURA_FRONTEND_BINARYEXPRAST_HPP
