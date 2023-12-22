//
// Created by robcholz on 12/20/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLECONSTANT_HPP
#define SSAKURA_FRONTEND_VARIABLECONSTANT_HPP

#include <utility>

#include <llvm/IR/Value.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "Type.hpp"


class VariableConstant : public Type {
public:
    using integer_t = int64_t;
    using floating_t = double_t;

    explicit VariableConstant(integer_t integer);

    explicit VariableConstant(floating_t floating);

    explicit VariableConstant(const std::string& number);

    llvm::Value* toLLVMConstant() const;

private:
    union Numeric {
        integer_t integer;
        floating_t floating;
    };

    Numeric constant;

    static std::pair<Numeric, ssa::Elementary> toNumeric(const std::string& number);
    static ssa::Elementary deductType(floating_t floating);
    static ssa::Elementary deductType(integer_t integer);
};

#endif //SSAKURA_FRONTEND_VARIABLECONSTANT_HPP
