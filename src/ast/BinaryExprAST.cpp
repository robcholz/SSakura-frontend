//
// Created by robcholz on 11/25/23.
//
#include <llvm/IR/Type.h>
#include "ast/BinaryExprAST.hpp"
#include "Info.hpp"
#include "type/BooleanComparison.hpp"


BinaryExprAST::BinaryExprAST(char op, std::unique_ptr<ExprAST> leftExprAst, std::unique_ptr<ExprAST> rightExprAst) {
    this->op = op;
    this->leftExprAst = std::move(leftExprAst);
    this->rightExprAst = std::move(rightExprAst);
}

llvm::Value* BinaryExprAST::codeGen() {
    const auto leftAst = leftExprAst->codeGen();
    const auto rightAst = rightExprAst->codeGen();
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& context = Info::getInstance().getLLVMContext();
    switch (op) {
        case '+': return ir_builder.CreateFAdd(leftAst, rightAst, "addtmp");
        case '-': return ir_builder.CreateFSub(leftAst, rightAst, "subtmp");
        case '*': return ir_builder.CreateFMul(leftAst, rightAst, "multmp");
        case '<': return Comparison::lessThan(leftAst,rightAst);
        case '>': return Comparison::greaterThan(leftAst,rightAst);
        default: return nullptr;
    }
}
