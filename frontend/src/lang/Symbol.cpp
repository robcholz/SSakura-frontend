//
// Created by robcholz on 2/2/24.
//
#include "ssa/lang/Symbol.hpp"

namespace ssa::internal {
std::unordered_map<Symbol, s_char_t> _reservedSymbolMap_e2s;
std::unordered_map<s_char_t, Symbol> _reservedSymbolMap_s2e;
}  // namespace ssa::internal