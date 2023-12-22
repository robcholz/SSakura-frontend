//
// Created by robcholz on 12/22/23.
//
#include <magic_enum/magic_enum.hpp>

#include "ElementaryType.hpp"


using namespace ssa;

void ElementaryType::init() {
    for (const auto& elementary: magic_enum::enum_values<Elementary>()) {
        const auto& str = std::string(magic_enum::enum_name<Elementary>(elementary));
        elementMap_e2s.insert({elementary, str});
        elementMap_s2e.insert({str, elementary});
    }
}

uint64_t ElementaryType::getBitwidth(Elementary type) {
    if (type == Elementary::I8 || type == Elementary::U8)
        return 8;
    if (type == Elementary::I16 || type == Elementary::U16
        || type == Elementary::F16)
        return 16;
    if (type == Elementary::I32 || type == Elementary::U32
        || type == Elementary::F32)
        return 32;
    if (type == Elementary::I64 || type == Elementary::U64
        || type == Elementary::F64)
        return 64;
    if (type == Elementary::I128 || type == Elementary::U128)
        return 128;
    if (type == Elementary::ISIZE || type == Elementary::USIZE)
        return Info::getInstance().getModule().getDataLayout().getPointerSizeInBits();
    throw std::logic_error("unhandled type");
}
