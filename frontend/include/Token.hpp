//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_TOKEN_HPP
#define SSAKURA_FRONTEND_TOKEN_HPP

#include "lang/Keyword.hpp"
#include "lang/Primitive.hpp"
#include "lang/Symbol.hpp"

namespace ssa {
class Lexer;

enum class TokenCategory {
  IDENTIFIER,
  // variables, functions,...
  KEYWORD,
  // reserved words & keyword
  LITERAL,
  // "1989" 'hi' 121331LU 198964
  SYMBOL,
  // :./#
  EOF_TERMINATOR,
  // indicate the termination of the file
};

class Token {
 public:
  Symbol getSymbol() const { return std::get<Symbol>(tokens); }

  Keyword getKeyword() const { return std::get<Keyword>(tokens); }

  const std::string& getLiteral() const {
    return std::get<std::string>(tokens);
  }

  const std::string& getIdentifier() const {
    return std::get<std::string>(tokens);
  }

  bool isSymbol() const { return category == TokenCategory::SYMBOL; }

  bool isKeyword() const { return category == TokenCategory::KEYWORD; }

  bool isLiteral() const { return category == TokenCategory::LITERAL; }

  bool isIdentifier() const { return category == TokenCategory::IDENTIFIER; }

  bool isEOF() const { return category == TokenCategory::EOF_TERMINATOR; }

  template <typename T>
  bool is() const {
    static_assert(std::is_same_v<T, Keyword> || std::is_same_v<T, Symbol>);
    if constexpr (std::is_same_v<T, Keyword>)
      return isKeyword();
    if constexpr (std::is_same_v<T, Symbol>)
      return isSymbol();
    return false;
  }

  template <typename T>
  const T& get() const {
    static_assert(std::is_same_v<T, Keyword> || std::is_same_v<T, Symbol>);
    return std::get<T>(tokens);
  }

 private:
  friend Lexer;
  /// symbol
  /// keyword
  /// literal | identifier
  std::variant<Symbol, Keyword, std::string> tokens;
  TokenCategory category;
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_TOKEN_HPP
