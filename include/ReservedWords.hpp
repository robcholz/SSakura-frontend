//
// Created by robcholz on 12/22/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_RESERVEDWORDS_HPP
#define SSAKURA_FRONTEND_RESERVEDWORDS_HPP

#include <string>
#include <unordered_map>
#include <spdlog/spdlog.h>


class ssa {
public:
    using ReservedSymbol_Underlying_t = char;

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

    enum class ReservedSymbol:ReservedSymbol_Underlying_t {
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

    enum class Elementary {
        I8,
        I16,
        I32,
        I64,
        I128,
        ISIZE,
        U8,
        U16,
        U32,
        U64,
        U128,
        USIZE,
        F16,
        F32,
        F64,
        VOID,
        NONE,
    };

    /// these are not keywords
    enum class BinaryOperator:int {
        ADD,
        SUBTRACT,
        MULTIPLE,
        DIVISION,
        MOD,
        GREATER,
        LESS,

        EQUAL,
        NOT,
        AND,
        OR,
    };

    static void init();

    /// \param number
    /// \return min bits required to store the number / the sign of that type
    static std::pair<uint64_t, bool> getMinBits(int64_t number);

    static uint64_t getMinBits(double_t number);

    static uint64_t getBitwidth(Elementary type);

    template<typename T>
    inline static const T& from_string(const std::string& key) {
        static_assert(std::is_same_v<T, Elementary> || std::is_same_v<T, Keyword>);
        if constexpr (std::is_same_v<T, Elementary>) {
            if (_elementMap_s2e.contains(key))
                return _elementMap_s2e.at(key);
            spdlog::error("No keyword found in s2e map");
        }
        if constexpr (std::is_same_v<T, Keyword>) {
            if (_keywordMap_s2e.contains(key))
                return _keywordMap_s2e.at(key);
            spdlog::error("No keyword found in s2k map");
        }
        static T t{};
        return t;
    }

    template<typename T>
    inline static const T& from_string(const ReservedSymbol_Underlying_t& key) {
        static_assert(std::is_same_v<T, ReservedSymbol>);
        if (_reservedSymbolMap_s2e.contains(key))
            return _reservedSymbolMap_s2e.at(key);
        spdlog::error("No keyword found in s2r map");
        static T t{};
        return t;
    }

    inline static std::string to_string(Elementary elementary) {
        if (_elementMap_e2s.contains(elementary))
            return _elementMap_e2s.at(elementary);
        spdlog::error("No keyword found in e2s map");
        return "";
    }

    inline static std::string to_string(Keyword keyword) {
        if (_keywordMap_e2s.contains(keyword))
            return _keywordMap_e2s.at(keyword);
        spdlog::error("No keyword found in k2s map");
        return "";
    }

    inline static std::string to_string(ReservedSymbol symbol) {
        std::string result;
        result = static_cast<ReservedSymbol_Underlying_t>(symbol);
        return result;
    }

    template<typename T>
    inline static bool contains(const std::string& strKey) {
        static_assert(std::is_same_v<T, Keyword>);
        return _keywordMap_s2e.contains(strKey);
    }

    template<typename T>
    inline static bool contains(const ReservedSymbol_Underlying_t& charKey) {
        static_assert(std::is_same_v<T, ReservedSymbol>);
        return _reservedSymbolMap_s2e.contains(charKey);
    }

private:
    inline static std::unordered_map<std::string, Elementary> _elementMap_s2e;
    inline static std::unordered_map<Elementary, std::string> _elementMap_e2s;
    inline static std::unordered_map<Keyword, std::string> _keywordMap_e2s;
    inline static std::unordered_map<std::string, Keyword> _keywordMap_s2e;
    inline static std::unordered_map<ReservedSymbol, ReservedSymbol_Underlying_t> _reservedSymbolMap_e2s;
    inline static std::unordered_map<ReservedSymbol_Underlying_t, ReservedSymbol> _reservedSymbolMap_s2e;
};

#endif //SSAKURA_FRONTEND_RESERVEDWORDS_HPP
