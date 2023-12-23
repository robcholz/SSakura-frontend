//
// Created by robcholz on 11/25/23.
//
#include <llvm/IR/Type.h>
#include "ast/BinaryExprAST.hpp"
#include "Info.hpp"
#include "type/BooleanComparison.hpp"


BinaryExprAST::BinaryExprAST(ssa::BinaryOperator op, std::unique_ptr<ExprAST> leftExprAst, std::unique_ptr<ExprAST> rightExprAst) {
    this->op = op;
    this->leftExprAst = std::move(leftExprAst);
    this->rightExprAst = std::move(rightExprAst);
}

llvm::Value* BinaryExprAST::codeGen() {
    const auto leftAst = leftExprAst->codeGen();
    const auto rightAst = rightExprAst->codeGen();
    auto& ir_builder = Info::getInstance().getIRBuilder();
    switch (this->op) {
        case ssa::BinaryOperator::ADD:
            return ir_builder.CreateFAdd(leftAst, rightAst, "addtmp");
        case ssa::BinaryOperator::MINUS:
            return ir_builder.CreateFSub(leftAst, rightAst, "subtmp");
        case ssa::BinaryOperator::MULTIPLE:
            return ir_builder.CreateFMul(leftAst, rightAst, "multmp");
        case ssa::BinaryOperator::LESS:
            return Comparison::lessThan(leftAst, rightAst);
        case ssa::BinaryOperator::GREATER:
            return Comparison::greaterThan(leftAst, rightAst);
        case ssa::BinaryOperator::EQUAL:
            return Comparison::equality(leftAst, rightAst);
        // TODO
    }
    throw std::logic_error("unhandled operator");
}
