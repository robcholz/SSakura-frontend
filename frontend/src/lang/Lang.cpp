//
// Created by robcholz on 2/1/24.
//
#include "lang/Lang.hpp"
#include <magic_enum/magic_enum.hpp>
#include "lang/Keyword.hpp"
#include "lang/Primitive.hpp"
#include "lang/Symbol.hpp"
#include "syntax/Checker.hpp"

using namespace ssa;

void Lang::init() {
  for (const auto& elementary : magic_enum::enum_values<Primitive>()) {
    const auto& str = std::string(magic_enum::enum_name<Primitive>(elementary));
    internal::_elementMap_e2s.insert({elementary, str});
    internal::_elementMap_s2e.insert({str, elementary});
  }

  for (const auto& keyword : magic_enum::enum_values<Keyword>()) {
    const auto& str = std::string(magic_enum::enum_name<Keyword>(keyword));
    internal::_keywordMap_e2s.insert({keyword, str});
    internal::_keywordMap_s2e.insert({str, keyword});
  }

  for (const auto& symbol : magic_enum::enum_values<Symbol>()) {
    const auto& ch = static_cast<s_char_t>(symbol);
    internal::_reservedSymbolMap_e2s.insert({symbol, ch});
    internal::_reservedSymbolMap_s2e.insert({ch, symbol});
  }

  static constexpr auto enum_values = magic_enum::enum_values<Checker::ErrorCode>();
  for (const auto& element : enum_values) {
    Checker::errorCodeMap.insert({element,std::string(magic_enum::enum_name(element))});
  }
}
