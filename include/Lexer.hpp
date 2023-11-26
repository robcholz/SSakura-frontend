//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LEXER_HPP
#define SSAKURA_FRONTEND_LEXER_HPP

#include <string>
#include <fstream>


class Lexer{
public:
    enum class Token : int {
        TOK_EOF = EOF, // file terminator
        PROCEDURE = -2, // function identifier
        IDENTIFIER = -4, // variable identifier
        NUMBER = -5, // numeric val
    };

    Lexer();
    ~Lexer()=default;

    void readFile(const std::string& filename);
    void closeFile();

    int getToken();
    std::string getNumberVal();
    std::string getIdentifierVal();
private:
    char getNextChar();

private:
    std::ifstream file;
    char lastChar;
    char currChar;

    std::string numberVal;   // Filled in if TOKEN_NUMBER
    std::string identifierVal;  // Filled in if TOKEN_IDENTIFIER
};

#endif //SSAKURA_FRONTEND_LEXER_HPP
