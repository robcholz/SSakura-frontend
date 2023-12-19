//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_NUMBEREXPRAST_HPP
#define SSAKURA_NUMBEREXPRAST_HPP

#include "ExprAST.hpp"


namespace llvm {
    class Value;
}

class NumberExprAST : public ExprAST {
public:
    explicit NumberExprAST(const std::string& number);

    llvm::Value* codeGen() final;

private:
    using integer_t = long;
    using floating_t = long double;

    enum Type {
        INTEGER,
        FLOATING,
    };

    Type type;
    integer_t integer;
    floating_t floating;
};

#endif //SSAKURA_NUMBEREXPRAST_HPP
