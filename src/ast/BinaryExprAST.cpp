//
// Created by robcholz on 11/25/23.
//
#include <llvm/IR/Type.h>
#include "ast/BinaryExprAST.hpp"
#include "Info.hpp"


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
        case ssa::BinaryOperator::DIVISON:
            return division(leftAst,rightAst);
        case ssa::BinaryOperator::MOD:
            return modulus(leftAst,rightAst);
        case ssa::BinaryOperator::LESS:
            return lessThan(leftAst, rightAst);
        case ssa::BinaryOperator::GREATER:
            return greaterThan(leftAst, rightAst);
        case ssa::BinaryOperator::EQUAL:
            return equality(leftAst, rightAst);
        case ssa::BinaryOperator::AND:
            return boolAnd(leftAst,rightAst);
        case ssa::BinaryOperator::OR:
            return boolOr(leftAst,rightAst);
        case ssa::BinaryOperator::NOT:
            return boolNot(rightAst);
    }
}

llvm::Value* BinaryExprAST::equality(llvm::Value* value) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& context = Info::getInstance().getLLVMContext();

    const auto type = value->getType();
    static llvm::Value* boolean_true = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 1);

    if (type->isFloatingPointTy()) {
        return ir_builder.CreateFCmpONE(value, boolean_true, "ifcond");
    }
    if (type->isIntegerTy()) {
        return ir_builder.CreateICmpEQ(value, boolean_true, "ifcond");
    }
    // TODO Handle
    spdlog::error("unhandled equality comparison type in BinaryExprAST");
    return nullptr;
}

llvm::Value* BinaryExprAST::equality(llvm::Value* left, llvm::Value* right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();

    trySyncType(&left, &right);

    const auto left_type = left->getType();
    const auto right_type = right->getType();

    if (left_type->isFloatingPointTy() && right_type->isFloatingPointTy()) {
        return ir_builder.CreateFCmpOEQ(left, right, "eqtmp");
    }
    if (left_type->isIntegerTy() && right_type->isIntegerTy()) {
        return ir_builder.CreateICmpEQ(left, right, "eqtmp");
    }
    // TODO handle
    throw std::logic_error("unhandled greatherthan comparison type");
}

llvm::Value* BinaryExprAST::greaterThan(llvm::Value* left, llvm::Value* right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();

    trySyncType(&left, &right);

    const auto left_type = left->getType();
    const auto right_type = right->getType();

    if (left_type->isFloatingPointTy() && right_type->isFloatingPointTy()) {
        return ir_builder.CreateFCmpUGT(left, right, "gttmp");
    }
    if (left_type->isIntegerTy() && right_type->isIntegerTy()) {
        return ir_builder.CreateICmpSGT(left, right, "gttmp");
    }
    // TODO handle
    throw std::logic_error("unhandled greatherthan comparison type");
}

llvm::Value* BinaryExprAST::lessThan(llvm::Value* left, llvm::Value* right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();

    trySyncType(&left, &right);

    const auto left_type = left->getType();
    const auto right_type = right->getType();

    if (left_type->isFloatingPointTy() && right_type->isFloatingPointTy()) {
        return ir_builder.CreateFCmpULT(left, right, "lstmp");
    }
    if (left_type->isIntegerTy() && right_type->isIntegerTy()) {
        return ir_builder.CreateICmpSLT(left, right, "lstmp");
    }
    // TODO handle
    throw std::logic_error("unhandled lessthan comparison type");
}

llvm::Value* BinaryExprAST::boolAnd(llvm::Value* left, llvm::Value* right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    return ir_builder.CreateAnd(left,right);
}

llvm::Value* BinaryExprAST::boolOr(llvm::Value* left, llvm::Value* right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    return ir_builder.CreateOr(left,right);
}

llvm::Value* BinaryExprAST::boolNot(llvm::Value* value) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    return ir_builder.CreateNot(value);
}

llvm::Value* BinaryExprAST::modulus(llvm::Value* left, llvm::Value* right) {
    if(!left->getType()->isIntegerTy()||!right->getType()->isIntegerTy()) {
        spdlog::error("Cannot apply binary operator% to non-integer type(s)!");
        std::terminate();
    }
    return Info::getInstance().getIRBuilder().CreateSRem(left, right);
}

llvm::Value* BinaryExprAST::division(llvm::Value* left, llvm::Value* right) {
    trySyncType(&left,&right);
    auto& ir_builder = Info::getInstance().getIRBuilder();
    if (left->getType()->isIntegerTy()) {
        return ir_builder.CreateSDiv(left, right);
    }
    if (left->getType()->isFloatingPointTy()) {
        return ir_builder.CreateFDiv(left, right);
    }
    throw std::logic_error("unhandled division comparison type");
}

void BinaryExprAST::trySyncType(llvm::Value** left, llvm::Value** right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& context = Info::getInstance().getLLVMContext();
    const auto left_type = (*left)->getType();
    const auto right_type = (*right)->getType();

    if (left_type->isIntegerTy() && right_type->isFloatingPointTy()) {
        *left = ir_builder.CreateSIToFP(*left, llvm::Type::getDoubleTy(context));
    }
    if (right_type->isIntegerTy() && left_type->isFloatingPointTy()) {
        *right = ir_builder.CreateSIToFP(*right, llvm::Type::getDoubleTy(context));
    }
}
