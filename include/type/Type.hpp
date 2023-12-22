//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_TYPE_HPP
#define SSAKURA_FRONTEND_TYPE_HPP

#include <string>

#include <llvm/IR/Type.h>

#include "ReservedWords.hpp"


class Type {
public:
    explicit Type(const std::string& type);

    explicit Type(ssa::Elementary type);

    ssa::Elementary getWrappedType() const;
    uint64_t getBitWidth() const;
    bool isFloat() const;
    bool isInteger() const;
    bool isSigned() const;
    const Type& getType() const;
    llvm::Type* toLLVMType() const;

private:
    uint64_t bitwidth;
    ssa::Elementary type;
};

#endif //SSAKURA_FRONTEND_TYPE_HPP
