//
// Created by robcholz on 12/20/23.
//
#include "type/VariableConstant.hpp"
#include "ElementaryType.hpp"
#include "tools/Utilities.hpp"


using namespace ssa;

VariableConstant::VariableConstant(integer_t integer)
    : Type(deductType(integer)),
      constant(Numeric{.integer = integer}) {
}

VariableConstant::VariableConstant(floating_t floating)
    : Type(deductType(floating)),
      constant(Numeric{.floating = floating}) {
}

VariableConstant::VariableConstant(const std::string& number)
    : Type(toNumeric(number).second),
      constant(toNumeric(number).first) {
}

std::pair<VariableConstant::Numeric, Elementary> VariableConstant::toNumeric(const std::string& number) {
    auto iterator = number.rbegin();
    const auto iterator_end = number.rend();

    integer_t integer_pt = 0;
    floating_t floating_pt = 0.f;
    size_t floating_pt_length = 0;
    bool is_integer = true;

    integer_t pow_pt = 0;
    bool is_scientific = false;

    size_t at = 1;
    char num_at = ' ';

    for (; iterator != iterator_end; ++iterator) {
        num_at = *iterator;
        if (isnumber(num_at)) {
            integer_pt = (num_at - '0') * static_cast<long>(at) + integer_pt;
            ++at;
        } else {
            if (num_at == '.' && is_integer) {
                // move the integer part to decimal part
                floating_pt = static_cast<floating_t>(integer_pt) / std::pow(10, at);
                is_integer = false;
                integer_pt = 0;
                floating_pt_length = at;
                at = 1;
            } // handle pure floating number
            else if (num_at == 'e' && !is_scientific) {
                pow_pt = integer_pt;
                is_scientific = true;
                integer_pt = 0;
                at = 1;
            }
        }
    }
    if (!is_integer)
        floating_pt += integer_pt;

    if (is_scientific) {
        if (is_integer) {
            integer_pt = static_cast<integer_t>(std::pow(integer_pt, pow_pt));
        } // base is integer
        else {
            if (floating_pt_length == pow_pt) {
                integer_pt = static_cast<integer_t>(std::pow(floating_pt, pow_pt));
                is_integer = true;
            } // if the decial pos equals pow part, it is still integer
            else {
                floating_pt = std::pow(floating_pt, pow_pt);
            } // floating for sure
        }
    }

    if (is_integer) {
        return std::make_pair(Numeric{.integer = integer_pt}, deductType(integer_pt));
    } else {
        return std::make_pair(Numeric{.floating = floating_pt}, deductType(floating_pt));
    }
}

Elementary VariableConstant::deductType(floating_t floating) {
    const auto min_bits = type::getMinBits(floating);
    auto type = Elementary::F64;
    if (min_bits == 16)
        type = Elementary::F16;
    else if (min_bits == 32)
        type = Elementary::F32;
    else if (min_bits == 64)
        type = Elementary::F64;
    return type;
}

Elementary VariableConstant::deductType(integer_t integer) {
    const auto min_bits = type::getMinBits(integer);
    std::string type_str;
    if (min_bits.second == true)
        type_str = "I";
    else
        type_str = "U";
    type_str.append(std::to_string(min_bits.first));
    return ElementaryType::toElementaryType(type_str);
}

llvm::Value* VariableConstant::toLLVMConstant() const {
    auto& context = Info::getInstance().getLLVMContext();
    const auto min_bits = getBitWidth();
    if (isFloat()) {
        if (min_bits == 16) {
            return llvm::ConstantFP::get(llvm::Type::getHalfTy(context), this->constant.floating);
        } // 16bit
        if (min_bits == 32) {
            return llvm::ConstantFP::get(llvm::Type::getFloatTy(context), this->constant.floating);
        } // f32
        if (min_bits == 64) {
            return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), this->constant.floating);
        } // f64
    }
    if (isInteger()) {
        return llvm::ConstantInt::get(context, llvm::APInt(min_bits, this->constant.integer, isSigned()));
    }
    // TODO handle
    std::terminate();
}
