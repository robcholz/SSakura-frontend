//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_KEYWORD_HPP
#define SSAKURA_FRONTEND_KEYWORD_HPP

#include <spdlog/spdlog.h>
#include <optional>
#include <string>
#include <unordered_map>

namespace ssa {
enum class Keyword {
  // general
  // function identifier
  PROCEDURE,
  // declaration of an identifier that can be referenced outside the module
  EXTERN,
  // c-style struct
  COLLECTION,
  // static variables, used in collection
  STATIC,
  // native c library call procedure wrapper
  NATIVE,
  // const type
  CONST,
  // package management

  // module is the name of the current ssakura source file
  MODULE,
  // import the given module
  IMPORT,
  // control flow

  // if branch
  IF,
  // else branch, must be paired with a if
  ELSE,
  // loop
  REPEAT,
  // loop
  UNTIL,
  // loop
  TIMES,
  // return a variable
  RETURN,
  // operators

  // boolean not operator
  NOT,
  // boolean and operator
  AND,
  // boolean or operator
  OR,
  // arithmetic operator, this is an exception, why not use %? fuck AP CSP
  MOD,
  // typedef

  // give an alias name to a type
  USE,
};

namespace internal {
extern std::unordered_map<Keyword, std::string> _keywordMap_e2s;
extern std::unordered_map<std::string, Keyword> _keywordMap_s2e;
}  // namespace internal

static std::string to_string(Keyword keyword) {
  if (internal::_keywordMap_e2s.contains(keyword))
    return internal::_keywordMap_e2s.at(keyword);
  spdlog::error("No keyword found in k2s map");
  return "";
}

template <typename T>
static std::optional<T> from_string(const std::string& key);

template <>
std::optional<Keyword> from_string(const std::string& key) {
  if (internal::_keywordMap_s2e.contains(key))
    return std::make_optional(internal::_keywordMap_s2e.at(key));
  spdlog::error("No keyword found in s2k map");
  return std::nullopt;
}

template <typename T>
static bool contains(const std::string& strKey) {
  static_assert(std::is_same_v<T, Keyword>);
  return internal::_keywordMap_s2e.contains(strKey);
}
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_KEYWORD_HPP
