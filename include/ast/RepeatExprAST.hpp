//
// Created by robcholz on 11/28/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_REPEATEXPRAST_HPP
#define SSAKURA_FRONTEND_REPEATEXPRAST_HPP


#include <memory>
#include "ExprAST.hpp"

class RepeatExprAST : public ExprAST {
public:
    enum class Type {
        REPEAT_UNTIL,
        REPEAT_TIMES
    };

    RepeatExprAST(const Type repeatType,std::unique_ptr<ExprAST> conditionExpr,std::unique_ptr<ExprAST> bodyExpr);
    llvm::Value* codeGen() final;
private:
    Type repeatType;
    std::unique_ptr<ExprAST> conditionExpr;
    std::unique_ptr<ExprAST> bodyExpr;
};

#endif //SSAKURA_FRONTEND_REPEATEXPRAST_HPP
