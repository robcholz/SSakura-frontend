//
// Created by robcholz on 11/25/23.
//
#include <iostream>

#include <magic_enum/magic_enum.hpp>

#include "Lexer.hpp"


using namespace ssa;

Lexer::Lexer() {
    this->lastChar = ' ';
    this->currChar = EOF;
    this->currTokenCategory = TokenCategory{};
}

void Lexer::readFile(const std::string& filename) {
    file.open(filename);
    while (!file.is_open());
}

void Lexer::closeFile() {
    file.close();
}

ReservedSymbol_Underlying_t Lexer::getNextChar() {
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
        if (keywordMap_s2e.contains(token.identifierVal)) {
            currTokenCategory = TokenCategory::KEYWORD;
            token.keyword = keywordMap_s2e.at(token.identifierVal);
            return /*keywordMap_s2k.at*/(token.identifierVal);
        } else {
            currTokenCategory = TokenCategory::IDENTIFIER;
            return "IDENTIFIER";
        }
    } // string

    // TokenCategory::LITERAL
    if (isDigit(lastChar) || equals(lastChar, '.')) {
        currTokenCategory = TokenCategory::LITERAL;
        token.literalVal.clear();
        while (isDigit(lastChar) || equals(lastChar, '.')) {
            token.literalVal.push_back(lastChar);
            lastChar = getNextChar();
        }
        return "NUMBER";
    }

    // comments
    if (equals(lastChar, ReservedSymbol::HASHTAG)) {
        do
            lastChar = getNextChar();
        while (!equals(lastChar,EOF) && !equals(lastChar, '\n') && !equals(lastChar, '\r'));
        if (!equals(lastChar,EOF)) {
            return getToken();
        }
    }

    if (reservedSymbolMap_e2s.contains(lastChar)) {
        currTokenCategory = TokenCategory::SYMBOL;
        token.symbolVal = static_cast<ReservedSymbol>(lastChar);
    }
    if (equals(lastChar,EOF)) {
        currTokenCategory = TokenCategory::EOF_TERMINATOR;
    }

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

void Lexer::init() {
    for (const auto& keyword: magic_enum::enum_values<Keyword>()) {
        const auto& str = std::string(magic_enum::enum_name<Keyword>(keyword));
        keywordMap_e2s.insert({keyword, str});
        keywordMap_s2e.insert({str, keyword});
    }
    for (const auto& symbol: magic_enum::enum_values<ReservedSymbol>()) {
        const auto& ch = static_cast<ReservedSymbol_Underlying_t>(symbol);
        reservedSymbolMap_s2e.insert({symbol, ch});
        reservedSymbolMap_e2s.insert({ch, symbol});
    }
}
