//
// Created by robcholz on 12/20/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_CHECKER_HPP
#define SSAKURA_FRONTEND_CHECKER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <format>
#include <magic_enum/magic_enum.hpp>

#include "ssa/Lexer.hpp"
#include "ssa/Parser.hpp"

namespace ssa {
class Lang;
class Checker {
 public:
  Checker(const Checker& other) = delete;

  Checker(Checker&& other) = delete;

  Checker& operator=(const Checker& other) = delete;

  Checker& operator=(Checker&& other) noexcept = delete;

  enum ErrorCode {
    ErrorUnexpectedSymbol,
    ErrorExpectedSymbol,
    ErrorUnexpectedKeyword,
  };

  static Checker& getInstance();

  static const Token& getNextVerifyThisToken(Parser* parser, Keyword keyword);

  static const Token& getNextVerifyThisToken(Parser* parser, Symbol symbol);

  static const Token& getNextVerifyNextToken(Parser* parser, Keyword keyword);

  static const Token& getNextVerifyNextToken(Parser* parser, Symbol symbol);

  static const Token& getNextVerifyNextToken(
      Parser* parser,
      const std::vector<Symbol>& symbols);

  static bool verifyCurrentToken(const Parser* parser,
                                 Keyword token,
                                 bool silence = false);

  static bool verifyCurrentToken(const Parser* parser,
                                 Symbol symbol,
                                 bool silence = false);

  static bool verifyEatCurrentToken(Parser* parser, Keyword keyword);

  static bool verifyEatCurrentToken(Parser* parser, Symbol symbol);

 private:
  friend Lang;
  inline static std::unordered_map<Checker::ErrorCode, std::string> errorCodeMap;

  Checker() = default;

  ~Checker() = default;

  inline static auto getErrorHintMap()
      -> const std::unordered_map<Checker::ErrorCode, std::string>& {
    return errorCodeMap;
  }

  template <typename T>
  inline static void emitError(ErrorCode error,
                               const T& expect,
                               const T& found) {
    std::cout << fmt::format("{} : {} but found {}",
                             getErrorHintMap().at(error), to_string(expect),
                             to_string(found))
              << std::endl;
  }

  template <typename T>
  inline static bool verify(ErrorCode error,
                            const T& expect,
                            const Token& token,
                            bool silence) {
    if (token.is<T>()) {
      const auto& found = token.get<T>();
      if (expect != found) {
        if (!silence)
          emitError(error, expect, found);
        return false;
      }
      return true;
    }
    return false;
  }

  template <typename T>
  inline static bool verify(ErrorCode error,
                            const std::vector<T>& expects,
                            const Token& token) {
    std::string is_found = "No Match";
    if (token.is<T>()) {
      const auto& found = token.get<T>();
      for (const auto& element : expects) {
        if (element == found) {
          return true;
        }
      }
      is_found = to_string(found);
      return false;
    }
    std::cout << fmt::format("{} : {}", getErrorHintMap().at(error), is_found)
              << std::endl;
    return false;
  }

  template <typename T>
  inline static const Token& getNextVerifyNextToken(Parser* parser,
                                                    ErrorCode error,
                                                    const T& expect) {
    const Token& token = parser->getNextToken();
    verify<T>(error, expect, token, false);
    return token;
  }

  template <typename T>
  inline static const Token& getNextVerifyNextToken(
      Parser* parser,
      ErrorCode error,
      const std::vector<T>& expects) {
    const Token& token = parser->getNextToken();
    verify<T>(error, expects, token);
    return token;
  }

  template <typename T>
  inline static const Token& getNextVerifyThisToken(Parser* parser,
                                                    ErrorCode error,
                                                    const T& expect) {
    verify<T>(error, expect, parser->getCurrentToken(), false);
    return parser->getNextToken();
  }

  template <typename T>
  inline static bool verifyCurrentToken(const Parser* parser,
                                        ErrorCode error,
                                        const T& expect,
                                        bool silence) {
    return verify<T>(error, expect, parser->getCurrentToken(), silence);
  }
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_CHECKER_HPP
