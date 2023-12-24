//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_TYPE_HPP
#define SSAKURA_FRONTEND_TYPE_HPP

#include <string>

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include "ReservedWords.hpp"


class Type {
public:
    enum Sub{
        INTEGER,
        FLOATING,
        STRING,
    };

    explicit Type(const std::string& type);

    explicit Type(ssa::Elementary type);

    ssa::Elementary getWrappedType() const;
    uint64_t getBitWidth() const;
    bool isFloat() const;
    bool isInteger() const;
    bool isSigned() const;
    bool isVoid() const;
    const Type& getType() const;
    llvm::Type* toLLVMType() const;

    static void tryStandardizeTypeValue(llvm::Value** left, llvm::Value** right);
    static void tryStandardizeValueType(llvm::Value** left, const llvm::Type* targetType);
    static void trySyncTypeValue(llvm::Value** left,llvm::Value** right);
    static llvm::Value* tryReturnSyncTypeValue(llvm::Value* left, llvm::Type* targetType);
    static std::string to_string(const llvm::Type* type);

private:
    uint64_t bitwidth;
    ssa::Elementary type;
};

#endif //SSAKURA_FRONTEND_TYPE_HPP
