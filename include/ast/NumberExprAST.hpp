//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_NUMBEREXPRAST_HPP
#define SSAKURA_NUMBEREXPRAST_HPP

#include "ExprAST.hpp"
#include "type/VariableConstant.hpp"


namespace llvm {
    class Value;
}

class NumberExprAST : public ExprAST {
public:
    explicit NumberExprAST(const std::string& number);

    llvm::Value* codeGen() final;

private:
    VariableConstant constant;
};

#endif //SSAKURA_NUMBEREXPRAST_HPP
