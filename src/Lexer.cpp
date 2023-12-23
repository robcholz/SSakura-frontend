//
// Created by robcholz on 11/25/23.
//
#include <iostream>

#include <magic_enum/magic_enum.hpp>

#include "Lexer.hpp"

#include <spdlog/spdlog.h>


Lexer::Lexer() {
    this->lastChar = ' ';
    this->currChar = EOF;
    this->token = Token{};
}

void Lexer::readFile(const std::string& filename) {
    file.open(filename);
    while (!file.is_open());
}

void Lexer::closeFile() {
    file.close();
}

ssa::ReservedSymbol_Underlying_t Lexer::getNextChar() {
    ssa::ReservedSymbol_Underlying_t ch;
    file.get(ch);
    return ch;
}

std::string Lexer::getToken() {
    while (isSpace(lastChar)) {
        lastChar = getNextChar();
    } // ignore space

    if (isAlpha(lastChar)) {
        pattern.clear();
        // TODO make sure a number literal format
        while (isNum(lastChar)) {
            pattern.push_back(lastChar);
            lastChar = getNextChar();
        }
        // TokenCategory::KEYWORD
        if (ssa::contains<ssa::Keyword>(pattern)) {
            token.category = TokenCategory::KEYWORD;
            token.tokens = ssa::from_string<ssa::Keyword>(pattern);
            return /*keywordMap_s2k.at*/(pattern);
        } else {
            token.category = TokenCategory::IDENTIFIER;
            token.tokens = pattern;
            return "IDENTIFIER";
        }
    } // string

    // TokenCategory::LITERAL
    if (isDigit(lastChar) || equals(lastChar, ssa::ReservedSymbol::DOT)) {
        token.category = TokenCategory::LITERAL;
        pattern.clear();
        while (isDigit(lastChar) || equals(lastChar, ssa::ReservedSymbol::DOT)) {
            pattern.push_back(lastChar);
            lastChar = getNextChar();
        }
        token.tokens = pattern;
        return "NUMBER";
    }

    // comments
    if (equals(lastChar, ssa::ReservedSymbol::HASHTAG)) {
        do
            lastChar = getNextChar();
        while (!equals(lastChar, ssa::ReservedSymbol::RETURN) &&
               !equals(lastChar, ssa::ReservedSymbol::EOF_FLAG) &&
               !equals(lastChar, ssa::ReservedSymbol::CARRIAGE_RETURN));
        if (!equals(lastChar, ssa::ReservedSymbol::EOF_FLAG)) {
            return getToken();
        }
    }

    if (ssa::contains<ssa::ReservedSymbol>(lastChar)) {
        token.category = TokenCategory::SYMBOL;
        pattern = lastChar;
        token.tokens = static_cast<ssa::ReservedSymbol>(lastChar);
    }
    if (equals(lastChar, ssa::ReservedSymbol::EOF_FLAG)) {
        token.category = TokenCategory::EOF_TERMINATOR;
    }

    currChar = lastChar;
    lastChar = getNextChar();
    std::string result;
    result = currChar;
    return result;
}

std::string Lexer::getTokenInString() const {
    return pattern;
}

std::string Lexer::getLiteralVal() const {
    return std::get<std::string>(token.tokens);
}

std::string Lexer::getIdentifierVal() const {
    return std::get<std::string>(token.tokens);
}

ssa::Keyword Lexer::getKeyword() const {
    return std::get<ssa::Keyword>(token.tokens);
}

ssa::ReservedSymbol Lexer::getSymbol() const {
    return std::get<ssa::ReservedSymbol>(token.tokens);
}

Lexer::TokenCategory Lexer::getTokenCategory() const {
    return token.category;
}
