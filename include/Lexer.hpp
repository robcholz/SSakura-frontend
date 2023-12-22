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


class Lexer{
public:
    using ReservedSymbol_Underlying_t=char;
    enum class Keyword {
        // general
        PROCEDURE, // function identifier
        EXTERN, // declaration of a identifier that can be referenced outside the module
        COLLECTION, // c-style struct
        STATIC, // static variables, used in collection
        NATIVE, // native c library call procedure wrapper
        CONST, // const type
        // package management
        MODULE, // module is the name of the current ssakura source file
        IMPORT, // import the given module
        // control flow
        IF, // if branch
        ELSE, // else branch, must be paired with a if
        REPEAT, // loop
        UNTIL, // loop
        TIMES, // loop
        RETURN, // return a variable
        // operators
        NOT, // boolean not operator
        AND, // boolean and operator
        OR, // boolean or operator
        MOD, // arithmetic operator, this is an exception, why not use %? fuck AP CSP
        // typedef
        USE, // give a alias name to a type
    };

    enum class ReservedSymbol:ReservedSymbol_Underlying_t {
        PLUS='+',
        HYPEN='-',
        ASTERISK='*',
        SLASH='/',
        BACKSLASH='\\',
        APOSTROPHE='\'',
        QUOTE='\'',
        LABRAC='<',
        RABRAC='>',
        LPAREN='(',
        RPAREN=')',
        LSBRAC='[',
        RSBRAC=']',
        LBRACE='{',
        RBRACE='}',
        COLON=':',
        COMMA=',',
        AT='@',
        HASHTAG='#',
    };

    enum class TokenCategory {
        IDENTIFIER, // variables, functions,...
        KEYWORD, // reserved words & keyword
        LITERAL, // "1989" 'hi' 121331LU 198964
        SYMBOL, // :./#
        EOF_TERMINATOR, // indicate the termination of the file
    };

    Lexer();
    ~Lexer()=default;

    void readFile(const std::string& filename);
    void closeFile();

    std::string getToken();
    std::string getNumberVal() const;
    std::string getIdentifierVal() const;

    TokenCategory getTokenCategory() const;

private:
    std::ifstream file;

    ReservedSymbol_Underlying_t lastChar;
    ReservedSymbol_Underlying_t currChar;
    TokenCategory currTokenCategory;

    struct Token {
        ReservedSymbol symbolVal; // filled in if SYMBOL
        std::string literalVal;   // filled in if LITERAL
        std::string identifierVal;  // filled in if IDENTIFIER
    }token;

    inline static std::unordered_map<Keyword,std::string> keywordMap;
    inline static std::unordered_map<ReservedSymbol,ReservedSymbol_Underlying_t> reservedSymbolMap;

    ReservedSymbol_Underlying_t getNextChar();

    void initialize();

    inline static bool allOf(const std::string_view& str,bool(*condition_function)(char)){
        if (str.length() == 1)
            return condition_function(str[0]);
        for (const auto& ch: str) {
            if (!condition_function(ch))
                return false;
        }
        return true;
    }

    inline static bool equals(const std::string_view& str,char str_1) {
        return str[0]==str_1;
    }

    inline static bool equals(char str,char str_1) {
        return str==str_1;
    }

    inline static bool isSpace(char str) {
        return isspace(str);
    }
    inline static bool isAlpha(char str) {
        return isalpha(str);
    }
    inline static bool isNum(char str) {
        return isalnum(str);
    }
    inline static bool isDigit(char str) {
        return isdigit(str);
    }
};

#endif //SSAKURA_FRONTEND_LEXER_HPP
