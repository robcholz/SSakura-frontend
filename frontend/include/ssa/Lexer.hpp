//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LEXER_HPP
#define SSAKURA_FRONTEND_LEXER_HPP

#include <deque>
#include <fstream>
#include <string>
#include <string_view>
#include <variant>

#include "Attribute.hpp"
#include "Token.hpp"

namespace ssa {
class Lexer {
 public:
  Lexer();

  ~Lexer() = default;

  void readFile(std::string_view filename);

  void closeFile();

  Token getToken();
  /// get but not eat the next token
  Token lookAhead();
  /// get but not eat the next n tokens
  Token lookAhead(std::size_t size);

 private:
  std::ifstream file;

  // temporary variables
  s_char_t lastChar;
  s_char_t currChar;
  std::string pattern;
  Token token;

  // token buffer for lookAhead feature
  std::deque<Token> tokenBuffer;

  s_char_t getNextChar();
  Token getNextToken();

  SSA_FORCE_INLINE static bool allOf(const std::string_view& str,
                                     bool (*condition_function)(char)) {
    if (str.length() == 1)
      return condition_function(str[0]);
    for (const auto& ch : str) {
      if (!condition_function(ch))
        return false;
    }
    return true;
  }

  SSA_FORCE_INLINE static bool equals(s_char_t str, Symbol symbol) {
    return str == static_cast<decltype(str)>(symbol);
  }

  SSA_FORCE_INLINE static bool isSpace(s_char_t str) { return isspace(str); }

  SSA_FORCE_INLINE static bool isAlpha(s_char_t str) { return isalpha(str); }

  SSA_FORCE_INLINE static bool isNum(s_char_t str) { return isalnum(str); }

  SSA_FORCE_INLINE static bool isDigit(s_char_t str) { return isdigit(str); }
};
}

#endif  // SSAKURA_FRONTEND_LEXER_HPP
