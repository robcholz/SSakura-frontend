//
// Created by robcholz on 11/25/23.
//
#include "Lexer.hpp"


Lexer::Lexer() {
    this->lastChar = ' ';
    this->currChar = -1;
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

int Lexer::getToken() {
    while (isspace(lastChar)) {
        lastChar = getNextChar();
    } // ignore space
    if (isalpha(lastChar)) {
        identifierVal.clear();
        while (isalnum(lastChar)) {
            identifierVal.push_back(lastChar);
            lastChar = getNextChar();
        }
        if (identifierVal == "PROCEDURE") {
            return (int) Token::PROCEDURE;
        } else
            return (int) Token::IDENTIFIER;
    } // string
    if (isdigit(lastChar) || lastChar == '.') {
        numberVal.clear();
        while (isdigit(lastChar) || lastChar == '.') {
            numberVal.push_back(lastChar);
            lastChar = getNextChar();
        }
        return (int) Token::NUMBER;
    }
    if (lastChar == '#') {
        do
            lastChar = getchar();
        while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');
        if (lastChar != EOF) {
            return getToken();
        }
    }
    currChar = lastChar;
    lastChar = getNextChar();
    return (int) currChar;
}

std::string Lexer::getNumberVal() {
    return numberVal;
}

std::string Lexer::getIdentifierVal() {
    return identifierVal;
}
