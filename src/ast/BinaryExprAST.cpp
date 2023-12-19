//
// Created by robcholz on 11/25/23.
//
#include <llvm/IR/Type.h>
#include "ast/BinaryExprAST.hpp"
#include "Info.hpp"


BinaryExprAST::BinaryExprAST(char op, std::unique_ptr<ExprAST> leftExprAst, std::unique_ptr<ExprAST> rightExprAst) {
    this->op=op;
    this->leftExprAst=std::move(leftExprAst);
    this->rightExprAst=std::move(rightExprAst);
}

llvm::Value* BinaryExprAST::codeGen() {
    const auto leftAst=leftExprAst->codeGen();
    const auto rightAst=rightExprAst->codeGen();
    switch (op) {
        case '+': return Info::getInstance().getIRBuilder().CreateFAdd(leftAst, rightAst, "addtmp");
        case '-': return Info::getInstance().getIRBuilder().CreateFSub(leftAst, rightAst, "subtmp");
        case '*': return Info::getInstance().getIRBuilder().CreateFMul(leftAst, rightAst, "multmp");
        case '<': {
            const auto leftAstTemp =Info::getInstance().getIRBuilder().CreateFCmpULT(leftAst, rightAst, "cmptmp");
            return Info::getInstance().getIRBuilder().CreateUIToFP(
                leftAstTemp, llvm::Type::getDoubleTy(Info::getInstance().getLLVMContext()), "booltmp");
        }
        default: return nullptr;
    }
}

