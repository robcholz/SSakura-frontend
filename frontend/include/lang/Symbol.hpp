//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_SYMBOL_HPP
#define SSAKURA_FRONTEND_SYMBOL_HPP

#include <cstdio>
#include <optional>
#include "Primitive.hpp"

namespace ssa {
enum class Symbol : s_char_t {
  PLUS = '+',
  HYPHEN = '-',
  ASTERISK = '*',
  SLASH = '/',
  EQUAL_SIGN = '=',
  BACKSLASH = '\\',
  APOSTROPHE = '\'',
  QUOTE = '\"',
  LABRAC = '<',
  RABRAC = '>',
  LPAREN = '(',
  RPAREN = ')',
  LSBRAC = '[',
  RSBRAC = ']',
  LBRACE = '{',
  RBRACE = '}',
  COLON = ':',
  COMMA = ',',
  DOT = '.',
  // annotation
  AT = '@',
  // comment
  HASHTAG = '#',

  EOF_FLAG = EOF,
  RETURN = '\n',
  CARRIAGE_RETURN = '\r',
};

namespace internal {
extern std::unordered_map<Symbol, s_char_t> _reservedSymbolMap_e2s;
extern std::unordered_map<s_char_t, Symbol> _reservedSymbolMap_s2e;
}  // namespace internal

inline static std::string to_string(Symbol symbol) {
  std::string result;
  result = static_cast<s_char_t>(symbol);
  return result;
}

template <typename T>
static std::optional<T> from_string(const s_char_t& key);

template <>
std::optional<Symbol> from_string(const s_char_t& key) {
  if (internal::_reservedSymbolMap_s2e.contains(key))
    return std::make_optional<Symbol>(internal::_reservedSymbolMap_s2e.at(key));
  spdlog::error("No keyword found in s2r map");
  return std::nullopt;
}

template <typename T>
inline static bool contains(const s_char_t& charKey) {
  static_assert(std::is_same_v<T, Symbol>);
  return internal::_reservedSymbolMap_s2e.contains(charKey);
}
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_SYMBOL_HPP
