//
// Created by robcholz on 12/19/23.
//
#include "rule/Type.hpp"

Type::Type(const std::string& type) {
    // TODO we assume that type is a elementary type
    this->type = ssa::from_string<ElementaryType>(type);
    this->bitwidth = ssa::getBitwidth(this->type);
}

Type::Type(ElementaryType type) {
    this->type=type;
    this->bitwidth=ssa::getBitwidth(type);
}


ElementaryType Type::getWrappedType() const {
    return type;
}

uint64_t Type::getBitWidth() const {
    return bitwidth;
}

bool Type::isFloat() const {
    if (type == ElementaryType::F32) return true;
    if (type == ElementaryType::F64) return true;
    return false;
}

bool Type::isInteger() const {
    if (type == ElementaryType::I8) return true;
    if (type == ElementaryType::I16) return true;
    if (type == ElementaryType::I32) return true;
    if (type == ElementaryType::I64) return true;
    if (type == ElementaryType::I128) return true;
    if (type == ElementaryType::ISIZE) return true;
    if (type == ElementaryType::U8) return true;
    if (type == ElementaryType::U16) return true;
    if (type == ElementaryType::U32) return true;
    if (type == ElementaryType::U64) return true;
    if (type == ElementaryType::U128) return true;
    if (type == ElementaryType::USIZE) return true;
    return false;
}

const Type& Type::getType() const {
    return *this;
}
