//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LEXER_HPP
#define SSAKURA_FRONTEND_LEXER_HPP

#include <string>
#include <string_view>
#include <variant>
#include <fstream>

#include "ReservedWords.hpp"


class Lexer {
public:
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
        ssa::ReservedSymbol getSymbol() const {
            return std::get<ssa::ReservedSymbol>(tokens);
        }

        ssa::Keyword getKeyword() const {
            return std::get<ssa::Keyword>(tokens);
        }

        std::string getLiteral() const {
            return std::get<std::string>(tokens);
        }

        std::string getIdentifier() const {
            return std::get<std::string>(tokens);
        }

        bool isSymbol() const { return category == TokenCategory::SYMBOL; }
        bool isKeyword() const { return category == TokenCategory::KEYWORD; }
        bool isLiteral() const { return category == TokenCategory::LITERAL; }
        bool isIdentifier() const { return category == TokenCategory::IDENTIFIER; }
        bool isEOF() const {return category==TokenCategory::EOF_TERMINATOR;}

        template<typename T>
        bool is() const{
            static_assert(std::is_same_v<T, ssa::Keyword> || std::is_same_v<T, ssa::ReservedSymbol>);
            if constexpr (std::is_same_v<T, ssa::Keyword>)
                return isKeyword();
            if constexpr (std::is_same_v<T, ssa::ReservedSymbol>)
                return isSymbol();
            return false;
        }

        template<typename T>
        const T& get()const {
            static_assert(std::is_same_v<T, ssa::Keyword> || std::is_same_v<T, ssa::ReservedSymbol>);
            return std::get<T>(tokens);
        }

    private:
        friend Lexer;
        /// symbol
        /// keyword
        /// literal | identifier
        std::variant<ssa::ReservedSymbol, ssa::Keyword, std::string> tokens;
        TokenCategory category;
    };

    Lexer();

    ~Lexer() = default;

    void readFile(const std::string& filename);

    void closeFile();

    Token getToken();

    /// valid only if getTokenCategory() not returns TokenCategory::EOF_TERMINATOR
    std::string getTokenInString() const;

    std::string getLiteralVal() const;

    std::string getIdentifierVal() const;

    ssa::Keyword getKeyword() const;

    ssa::ReservedSymbol getSymbol() const;

    TokenCategory getTokenCategory() const;

private:
    std::ifstream file;

    ssa::ReservedSymbol_Underlying_t lastChar;
    ssa::ReservedSymbol_Underlying_t currChar;
    std::string pattern;

    Token token;

    ssa::ReservedSymbol_Underlying_t getNextChar();

    inline static bool allOf(const std::string_view& str, bool (*condition_function)(char)) {
        if (str.length() == 1)
            return condition_function(str[0]);
        for (const auto& ch: str) {
            if (!condition_function(ch))
                return false;
        }
        return true;
    }

    inline static bool equals(ssa::ReservedSymbol_Underlying_t str, ssa::ReservedSymbol symbol) {
        return str == static_cast<ssa::ReservedSymbol_Underlying_t>(symbol);
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
