//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LEXER_HPP
#define SSAKURA_FRONTEND_LEXER_HPP

#include <string>
#include <string_view>
#include <unordered_map>
#include <fstream>

#include "ReservedWords.hpp"


class Lexer{
public:
    enum class TokenCategory {
        IDENTIFIER, // variables, functions,...
        KEYWORD, // reserved words & keyword
        LITERAL, // "1989" 'hi' 121331LU 198964
        SYMBOL, // :./#
        EOF_TERMINATOR, // indicate the termination of the file
    };

    Lexer();
    ~Lexer()=default;

    static void init();

    void readFile(const std::string& filename);
    void closeFile();

    std::string getToken();
    std::string getNumberVal() const;
    std::string getIdentifierVal() const;

    TokenCategory getTokenCategory() const;

private:
    std::ifstream file;

    ssa::ReservedSymbol_Underlying_t lastChar;
    ssa::ReservedSymbol_Underlying_t currChar;
    TokenCategory currTokenCategory;

    struct Token {
        ssa::ReservedSymbol symbolVal; // filled in if SYMBOL
        ssa::Keyword keyword;
        std::string literalVal;   // filled in if LITERAL
        std::string identifierVal;  // filled in if IDENTIFIER
    }token;

    inline static std::unordered_map<ssa::Keyword,std::string> keywordMap_e2s;
    inline static std::unordered_map<std::string,ssa::Keyword> keywordMap_s2e;
    inline static std::unordered_map<ssa::ReservedSymbol,ssa::ReservedSymbol_Underlying_t> reservedSymbolMap_s2e;
    inline static std::unordered_map<ssa::ReservedSymbol_Underlying_t,ssa::ReservedSymbol> reservedSymbolMap_e2s;

    ssa::ReservedSymbol_Underlying_t getNextChar();

    inline static bool allOf(const std::string_view& str,bool(*condition_function)(char)){
        if (str.length() == 1)
            return condition_function(str[0]);
        for (const auto& ch: str) {
            if (!condition_function(ch))
                return false;
        }
        return true;
    }

    inline static bool equals(ssa::ReservedSymbol_Underlying_t str, ssa::ReservedSymbol symbol) {
        return str==static_cast<ssa::ReservedSymbol_Underlying_t>(symbol);
    }

    inline static bool equals(ssa::ReservedSymbol_Underlying_t str,ssa::ReservedSymbol_Underlying_t str_1) {
        return str==str_1;
    }

    inline static bool isSpace(ssa::ReservedSymbol_Underlying_t str) {
        return isspace(str);
    }
    inline static bool isAlpha(ssa::ReservedSymbol_Underlying_t str) {
        return isalpha(str);
    }
    inline static bool isNum(ssa::ReservedSymbol_Underlying_t str) {
        return isalnum(str);
    }
    inline static bool isDigit(ssa::ReservedSymbol_Underlying_t str) {
        return isdigit(str);
    }
};

#endif //SSAKURA_FRONTEND_LEXER_HPP
