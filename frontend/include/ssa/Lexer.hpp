//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LEXER_HPP
#define SSAKURA_FRONTEND_LEXER_HPP

#include <fstream>
#include <string>
#include <string_view>
#include <variant>

#include "Token.hpp"

namespace ssa {
class Lexer {
 public:
  Lexer();

  ~Lexer() = default;

  void readFile(const std::string& filename);

  void closeFile();

  Token getToken();

  std::string getLiteralVal() const;

  std::string getIdentifierVal() const;

  Keyword getKeyword() const;

  Symbol getSymbol() const;

  TokenCategory getTokenCategory() const;

 private:
  std::ifstream file;

  s_char_t lastChar;
  s_char_t currChar;
  std::string pattern;

  Token token;

  s_char_t getNextChar();

  inline static bool allOf(const std::string_view& str,
                           bool (*condition_function)(char)) {
    if (str.length() == 1)
      return condition_function(str[0]);
    for (const auto& ch : str) {
      if (!condition_function(ch))
        return false;
    }
    return true;
  }

  inline static bool equals(s_char_t str, Symbol symbol) {
    return str == static_cast<decltype(str)>(symbol);
  }

  inline static bool isSpace(s_char_t str) { return isspace(str); }

  inline static bool isAlpha(s_char_t str) { return isalpha(str); }

  inline static bool isNum(s_char_t str) { return isalnum(str); }

  inline static bool isDigit(s_char_t str) { return isdigit(str); }
};
}

#endif  // SSAKURA_FRONTEND_LEXER_HPP
