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

    /// \param value the boolean value (1bit integer)
    static llvm::Value* equality(llvm::Value* value);
    static llvm::Value* equality(llvm::Value* left,llvm::Value* right);
    static llvm::Value* greaterThan(llvm::Value* left, llvm::Value* right);
    static llvm::Value* lessThan(llvm::Value* left, llvm::Value* right);
    static llvm::Value* boolAnd(llvm::Value* left,llvm::Value* right);
    static llvm::Value* boolOr(llvm::Value* left,llvm::Value* right);
    static llvm::Value* boolNot(llvm::Value* value);
    static llvm::Value* modulus(llvm::Value* left,llvm::Value* right);
    static llvm::Value* division(llvm::Value* left,llvm::Value* right);
    static void tryStandardizeType(llvm::Value** left, llvm::Value** right);
    static void trySyncType(llvm::Value** left,llvm::Value** right);
};

#endif //SSAKURA_FRONTEND_BINARYEXPRAST_HPP
