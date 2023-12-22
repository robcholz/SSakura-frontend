//
// Created by robcholz on 11/25/23.
//
#include <iostream>

#include <magic_enum/magic_enum.hpp>

#include "Lexer.hpp"


Lexer::Lexer() {
    this->lastChar = ' ';
    this->currChar = EOF;
    this->currTokenCategory = TokenCategory{};
    initialize();
}

void Lexer::readFile(const std::string& filename) {
    file.open(filename);
    while (!file.is_open());
}

void Lexer::closeFile() {
    file.close();
}

Lexer::ReservedSymbol_Underlying_t Lexer::getNextChar() {
    ReservedSymbol_Underlying_t ch;
    file.get(ch);
    return ch;
}

std::string Lexer::getToken() {
    while (isSpace(lastChar)) {
        lastChar = getNextChar();
    } // ignore space

    if (isAlpha(lastChar)) {
        token.identifierVal.clear();
        // TODO, make sure a number literal format
        while (isNum(lastChar)) {
            token.identifierVal.push_back(lastChar);
            lastChar = getNextChar();
        }

        // TokenCategory::KEYWORD
        if (token.identifierVal == "PROCEDURE") {
            return "PROCEDURE";
        } else if (token.identifierVal == "IF") {
            return "IF";
        } else if (token.identifierVal == "ELSE") {
            return "ELSE";
        } else if (token.identifierVal == "EXTERN") {
            return "EXTERN";
        } else if (token.identifierVal == "RETURN") {
            return "RETURN";
        } else if (token.identifierVal == "REPEAT") {
            return "REPEAT";
        } else if (token.identifierVal == "UNTIL") {
            return "UTIL";
        } else if (token.identifierVal == "TIMES") {
            return "TIMES";
        } else {
            return "IDENTIFIER";
        }
    } // string

    // TokenCategory::LITERAL
    if (isDigit(lastChar) || equals(lastChar, '.')) {
        token.literalVal.clear();
        while (isDigit(lastChar) || equals(lastChar, '.')) {
            token.literalVal.push_back(lastChar);
            lastChar = getNextChar();
        }
        currTokenCategory = TokenCategory::LITERAL;
        return "NUMBER";
    }

    if (equals(lastChar, '#')) {
        do
            lastChar = getNextChar();
        while (!equals(lastChar,EOF) && !equals(lastChar, '\n') && !equals(lastChar, '\r'));
        if (!equals(lastChar,EOF)) {
            return getToken();
        }
    } // comments
    currChar = lastChar;
    lastChar = getNextChar();
    std::string result;
    result = currChar;
    return result;
}

std::string Lexer::getNumberVal() const {
    return token.literalVal;
}

std::string Lexer::getIdentifierVal() const {
    return token.identifierVal;
}

Lexer::TokenCategory Lexer::getTokenCategory() const {
    return currTokenCategory;
}

void Lexer::initialize() {
    for (const auto& keyword: magic_enum::enum_values<Keyword>()) {
        keywordMap.insert({keyword, std::string(magic_enum::enum_name<Keyword>(keyword))});
    }

    for (const auto& symbol: magic_enum::enum_values<ReservedSymbol>()) {
        reservedSymbolMap.insert({symbol, static_cast<ReservedSymbol_Underlying_t>(symbol)});
    }
}
