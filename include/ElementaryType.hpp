//
// Created by robcholz on 12/19/23.
//

#pragma once

#ifndef SSAKURA_FRONTEND_ELEMENTARYTYPE_HPP
#define SSAKURA_FRONTEND_ELEMENTARYTYPE_HPP

#include <string>
#include <unordered_map>
#include <type_traits>

#include "Info.hpp"


enum class ElementaryType {
    I8,
    I16,
    I32,
    I64,
    I128,
    ISIZE,
    U8,
    U16,
    U32,
    U64,
    U128,
    USIZE,

    F32,
    F64,
};

namespace ssa {
    // TODO use fixed-container
    static std::unordered_map<std::string, ElementaryType> str2type = {
        {"I8", ElementaryType::I8},
        {"I16", ElementaryType::I16},
        {"I32", ElementaryType::I32},
        {"I64", ElementaryType::I64},
        {"I128", ElementaryType::I128},
        {"U8", ElementaryType::U8},
        {"U16", ElementaryType::U16},
        {"U32", ElementaryType::U32},
        {"U64", ElementaryType::U64},
        {"U128", ElementaryType::U128},
        {"USIZE", ElementaryType::USIZE},
        {"F32", ElementaryType::F32},
        {"F64", ElementaryType::F64},
    };
    // TODO use fixed-container
    static std::unordered_map<ElementaryType, std::string> type2str = {
        {ElementaryType::I8, "I8"},
        {ElementaryType::I16, "I16"},
        {ElementaryType::I32, "I32"},
        {ElementaryType::I64, "I64"},
        {ElementaryType::I128, "I128"},
        {ElementaryType::ISIZE, "ISIZE"},
        {ElementaryType::U8, "U8"},
        {ElementaryType::U16, "U16"},
        {ElementaryType::U32, "U32"},
        {ElementaryType::U64, "U64"},
        {ElementaryType::U128, "U128"},
        {ElementaryType::USIZE, "USIZE"},
        {ElementaryType::F32, "F32"},
        {ElementaryType::F64, "F64"},
    };

    inline uint64_t getBitwidth(ElementaryType type) {
        if (type == ElementaryType::I8 || type == ElementaryType::U8)
            return 8;
        if (type == ElementaryType::I16 || type == ElementaryType::U16)
            return 16;
        if (type == ElementaryType::I32 || type == ElementaryType::U32
            || type == ElementaryType::F32)
            return 32;
        if (type == ElementaryType::I64 || type == ElementaryType::U64
            || type == ElementaryType::F64)
            return 64;
        if (type == ElementaryType::I128 || type == ElementaryType::U128)
            return 128;
        if (type == ElementaryType::ISIZE || type == ElementaryType::USIZE)
            return Info::getInstance().getModule().getDataLayout().getPointerSizeInBits();
        std::exit(1);
    }

    template<typename T>
    ElementaryType from_string(const std::string& type) {
        static_assert(std::is_same_v<T, ElementaryType>);
        return str2type.at(type);
    }

    inline std::string to_string(ElementaryType type) {
        return type2str.at(type);
    }
}


#endif //SSAKURA_FRONTEND_ELEMENTARYTYPE_HPP
