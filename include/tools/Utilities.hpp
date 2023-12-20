//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_UTILITIES_HPP
#define SSAKURA_FRONTEND_UTILITIES_HPP

#include <utility>
#include <cmath>
#include <limits>

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace ssa::type {
    /// \param number
    /// \return min bits required to store the number / the sign of that type
    static std::pair<uint64_t, bool> getMinBits(int64_t number) {
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

    static uint64_t getMinBits(double_t number) {
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
}


#endif //SSAKURA_FRONTEND_UTILITIES_HPP
