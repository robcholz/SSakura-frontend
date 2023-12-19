//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_EXPRAST_HPP
#define SSAKURA_FRONTEND_EXPRAST_HPP


namespace llvm {
    class Value;
}

class ExprAST {
public:
    virtual ~ExprAST() = default;

    virtual llvm::Value* codeGen() =0;
};

#endif //SSAKURA_FRONTEND_EXPRAST_HPP
