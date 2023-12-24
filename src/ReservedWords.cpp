//
// Created by robcholz on 12/23/23.
//
#include <utility>
#include <cmath>
#include <limits>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <magic_enum/magic_enum.hpp>

#include "ReservedWords.hpp"
#include "Info.hpp"


void ssa::init() {
    for (const auto& elementary: magic_enum::enum_values<Elementary>()) {
        const auto& str = std::string(magic_enum::enum_name<Elementary>(elementary));
        _elementMap_e2s.insert({elementary, str});
        _elementMap_s2e.insert({str, elementary});
    }

    for (const auto& keyword: magic_enum::enum_values<Keyword>()) {
        const auto& str = std::string(magic_enum::enum_name<Keyword>(keyword));
        _keywordMap_e2s.insert({keyword, str});
        _keywordMap_s2e.insert({str, keyword});
    }
    for (const auto& symbol: magic_enum::enum_values<ReservedSymbol>()) {
        const auto& ch = static_cast<ReservedSymbol_Underlying_t>(symbol);
        _reservedSymbolMap_e2s.insert({symbol, ch});
        _reservedSymbolMap_s2e.insert({ch, symbol});
    }
}

std::pair<uint64_t, bool> ssa::getMinBits(int64_t number) {
    // bits can only be 8,16,32,64,128
    bool is_signed = number < 0;
    uint64_t min_bits;
    if (is_signed) {
        min_bits = std::ceil(std::log2(std::abs(number)) + 1);
    } // has negative part
    else {
        min_bits = std::ceil(std::log2(number + 1));
    } // pure positve
    min_bits = (min_bits / 8 + 1) * 8;
    return std::make_pair(min_bits, is_signed);
}

uint64_t ssa::getMinBits(double_t number) {
    using f16_t = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<16>>;
    using f32_t = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<32>>;
    using f64_t = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<64>>;

    static const f16_t F16_MIN = std::numeric_limits<f16_t>::min();
    static const f16_t F16_MAX = std::numeric_limits<f16_t>::max();
    static const f64_t F32_MIN = std::numeric_limits<f32_t>::min();
    static const f64_t F32_MAX = std::numeric_limits<f32_t>::max();
    static const f64_t F64_MIN = std::numeric_limits<f64_t>::min();
    static const f64_t F64_MAX = std::numeric_limits<f64_t>::max();

    if (F16_MIN <= number && number <= F16_MAX)
        return 16;
    if (F32_MIN <= number && number <= F32_MAX)
        return 32;
    return 64;
}

uint64_t ssa::getBitwidth(Elementary type) {
    if (type == Elementary::VOID)
        return 0;
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
