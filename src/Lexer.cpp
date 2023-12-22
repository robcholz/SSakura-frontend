//
// Created by robcholz on 11/25/23.
//
#include "Lexer.hpp"

#include <iostream>


Lexer::Lexer() {
    this->lastChar = ' ';
    this->currChar = EOF;
}

void Lexer::readFile(const std::string& filename) {
    file.open(filename);
    while (!file.is_open());
}

void Lexer::closeFile() {
    file.close();
}

char Lexer::getNextChar() {
    char ch;
    file.get(ch);
    return ch;
}

std::string Lexer::getToken() {
    while (isSpace(lastChar)) {
        lastChar = getNextChar();
    } // ignore space
    if (isAlpha(lastChar)) {
        identifierVal.clear();
        // TODO, make sure a number literal format
        while (isNum(lastChar)) {
            identifierVal.push_back(lastChar);
            lastChar = getNextChar();
        }
        if (identifierVal == "PROCEDURE") {
            return "PROCEDURE";
        } else if (identifierVal == "IF") {
            return "IF";
        } else if (identifierVal == "ELSE") {
            return "ELSE";
        } else if (identifierVal == "EXTERN") {
            return "EXTERN";
        } else if (identifierVal == "RETURN") {
            return "RETURN";
        } else if (identifierVal == "REPEAT") {
            return "REPEAT";
        } else if (identifierVal == "UNTIL") {
            return "UTIL";
        } else if (identifierVal == "TIMES") {
            return "TIMES";
        } else {
            return "IDENTIFIER";
        }
    } // string
    if (isDigit(lastChar) || equals(lastChar, '.')) {
        numberVal.clear();
        while (isDigit(lastChar) || equals(lastChar, '.')) {
            numberVal.push_back(lastChar);
            lastChar = getNextChar();
        }
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
    return numberVal;
}

std::string Lexer::getIdentifierVal() const {
    return identifierVal;
}

bool Lexer::isSpace(const std::string_view& str) {
    return allOf(str, [](const char ch)-> bool { return ch == ' '; });
}

bool Lexer::isSpace(char str) {
    return isspace(str);
}

bool Lexer::isAlpha(const std::string_view& str) {
    return allOf(str, [](const char ch)-> bool { return isalpha(ch); });
}

bool Lexer::isAlpha(char str) {
    return isalpha(str);
}

bool Lexer::isNum(const std::string_view& str) {
    return allOf(str, [](const char ch)-> bool { return isalnum(ch); });
}

bool Lexer::isNum(char str) {
    return isalnum(str);
}

bool Lexer::isDigit(const std::string_view& str) {
    return allOf(str, [](const char ch)-> bool { return isdigit(ch); });
}

bool Lexer::isDigit(char str) {
    return isdigit(str);
}
