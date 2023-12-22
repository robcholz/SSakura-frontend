//
// Created by robcholz on 12/20/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_BOOLEANCOMPARISON_HPP
#define SSAKURA_FRONTEND_BOOLEANCOMPARISON_HPP

#include "Info.hpp"


class Comparison {
public:
    /// \param value the boolean value (1bit integer)
    static llvm::Value* equality(llvm::Value* value) {
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
        throw std::logic_error("unhandled equality comparison type");
    }

    static llvm::Value* equality(llvm::Value* left,llvm::Value* right) {
        auto& ir_builder = Info::getInstance().getIRBuilder();

        tryCastType(&left, &right);

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

    static llvm::Value* greaterThan(llvm::Value* left, llvm::Value* right) {
        auto& ir_builder = Info::getInstance().getIRBuilder();

        tryCastType(&left, &right);

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

    static llvm::Value* lessThan(llvm::Value* left, llvm::Value* right) {
        auto& ir_builder = Info::getInstance().getIRBuilder();

        tryCastType(&left, &right);

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

private:
    static void tryCastType(llvm::Value** left, llvm::Value** right) {
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
};

#endif //SSAKURA_FRONTEND_BOOLEANCOMPARISON_HPP
