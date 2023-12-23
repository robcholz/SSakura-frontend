//
// Created by robcholz on 12/19/23.
//
#include "type/Type.hpp"
#include "Info.hpp"
#include "ReservedWords.hpp"


Type::Type(const std::string& type) {
    // TODO we assume that type is a elementary type
    this->type = ssa::from_string<ssa::Elementary>(type);
    this->bitwidth = ssa::getBitwidth(this->type);
}

Type::Type(ssa::Elementary type) {
    this->type = type;
    this->bitwidth = ssa::getBitwidth(type);
}


ssa::Elementary Type::getWrappedType() const {
    return type;
}

uint64_t Type::getBitWidth() const {
    return bitwidth;
}

bool Type::isFloat() const {
    if (type == ssa::Elementary::F16) return true;
    if (type == ssa::Elementary::F32) return true;
    if (type == ssa::Elementary::F64) return true;
    return false;
}

bool Type::isInteger() const {
    if (type == ssa::Elementary::I8) return true;
    if (type == ssa::Elementary::I16) return true;
    if (type == ssa::Elementary::I32) return true;
    if (type == ssa::Elementary::I64) return true;
    if (type == ssa::Elementary::I128) return true;
    if (type == ssa::Elementary::ISIZE) return true;
    if (type == ssa::Elementary::U8) return true;
    if (type ==ssa:: Elementary::U16) return true;
    if (type ==ssa:: Elementary::U32) return true;
    if (type == ssa::Elementary::U64) return true;
    if (type == ssa::Elementary::U128) return true;
    if (type == ssa::Elementary::USIZE) return true;
    return false;
}

bool Type::isSigned() const {
    if(isFloat())
        return true;
    if(isInteger()) {
        if (type == ssa::Elementary::I8) return true;
        if (type == ssa::Elementary::I16) return true;
        if (type == ssa::Elementary::I32) return true;
        if (type == ssa::Elementary::I64) return true;
        if (type == ssa::Elementary::I128) return true;
        if (type == ssa::Elementary::ISIZE) return true;
        return false;
    }
    return false;
}

const Type& Type::getType() const {
    return *this;
}

llvm::Type* Type::toLLVMType() const {
    auto& context = Info::getInstance().getLLVMContext();
    if (isInteger()) {
        return llvm::IntegerType::get(context, getBitWidth());
    } else if (isFloat()) {
        const auto bit_width = getBitWidth();
        if (bit_width == 16) {
            return llvm::Type::getHalfTy(context);
        }
        if (bit_width == 32) {
            return llvm::Type::getFloatTy(context);
        }
        if (bit_width==64) {
            return llvm::Type::getDoubleTy(context);
        }
        // TODO f128?
    }
    // TODO handle exception type
    std::terminate();
}
