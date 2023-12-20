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
        auto& context=Info::getInstance().getLLVMContext();
        const auto type = value->getType();
        static llvm::Value* boolean_true = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context),1);

        if (type->isFloatingPointTy()) {
            return ir_builder.CreateFCmpONE(value, boolean_true, "ifcond");
        }
        if (type->isIntegerTy()) {
            return ir_builder.CreateICmpEQ(value, boolean_true, "ifcond");
        }
        // TODO Handle
        std::terminate();
    }

    static llvm::Value* greaterThan(llvm::Value* left, llvm::Value* right) {
    }

    static llvm::Value* lessThan(llvm::Value* left, llvm::Value* right) {
        auto& ir_builder = Info::getInstance().getIRBuilder();
        auto& context = Info::getInstance().getLLVMContext();
        auto left_type = left->getType();
        auto right_type = right->getType();

        if (left_type->isIntegerTy() && right_type->isFloatingPointTy()) {
            left = ir_builder.CreateSIToFP(left, llvm::Type::getDoubleTy(context));
            left_type = left->getType();
        }
        if (right_type->isIntegerTy() && left_type->isFloatingPointTy()) {
            right = ir_builder.CreateSIToFP(right, llvm::Type::getDoubleTy(context));
            right_type = right->getType();
        }

        if (left_type->isFloatingPointTy() && right_type->isFloatingPointTy()) {
            return ir_builder.CreateFCmpULT(left, right, "lessthantmp");
        }
        if (left_type->isIntegerTy() && right_type->isIntegerTy()) {
            return ir_builder.CreateICmpSLT(left, right, "lessthantmp");
        }


        // TODO handle
        std::terminate();
    }
};

#endif //SSAKURA_FRONTEND_BOOLEANCOMPARISON_HPP
