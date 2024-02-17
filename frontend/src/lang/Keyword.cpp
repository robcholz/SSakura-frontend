//
// Created by robcholz on 2/2/24.
//
#include "lang/Keyword.hpp"

namespace ssa::internal {
std::unordered_map<Keyword, std::string> _keywordMap_e2s;
std::unordered_map<std::string, Keyword> _keywordMap_s2e;
} // namespace ssa::internal
