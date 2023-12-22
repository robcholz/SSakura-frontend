//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BINARYEXPRAST_HPP
#define SSAKURA_FRONTEND_BINARYEXPRAST_HPP

#include <memory>
#include <string>
#include "ExprAST.hpp"


class BinaryExprAST : public ExprAST {
public:
    explicit BinaryExprAST(std::string op,std::unique_ptr<ExprAST> leftExprAst,std::unique_ptr<ExprAST> rightExprAst);
    llvm::Value* codeGen() final;
private:
    std::string op;
    std::unique_ptr<ExprAST> leftExprAst;
    std::unique_ptr<ExprAST> rightExprAst;
};

#endif //SSAKURA_FRONTEND_BINARYEXPRAST_HPP
