//
// Created by robcholz on 11/25/23.
//
#include <llvm/IR/Type.h>
#include "ast/BinaryExprAST.hpp"
#include "Info.hpp"
#include "type/BooleanComparison.hpp"


BinaryExprAST::BinaryExprAST(std::string op, std::unique_ptr<ExprAST> leftExprAst, std::unique_ptr<ExprAST> rightExprAst) {
    this->op = op;
    this->leftExprAst = std::move(leftExprAst);
    this->rightExprAst = std::move(rightExprAst);
}

llvm::Value* BinaryExprAST::codeGen() {
    const auto leftAst = leftExprAst->codeGen();
    const auto rightAst = rightExprAst->codeGen();
    auto& ir_builder = Info::getInstance().getIRBuilder();
    if (op == "+")
        return ir_builder.CreateFAdd(leftAst, rightAst, "addtmp");
    if (op == "-")
        return ir_builder.CreateFSub(leftAst, rightAst, "subtmp");
    if (op == "*")
        return ir_builder.CreateFMul(leftAst, rightAst, "multmp");
    if (op == "<")
        return Comparison::lessThan(leftAst, rightAst);
    if (op == ">")
        return Comparison::greaterThan(leftAst, rightAst);
    if (op == "=")
        return Comparison::equality(leftAst, rightAst);
    throw std::logic_error("unhandled operator");
}
