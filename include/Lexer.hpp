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

        // general
        PROCEDURE = -2, // function identifier
        EXTERN=-3, // declaration of a identifier that can be referenced outside the module
        COLLECTION=-4, // c-style struct
        STATIC=-5, // static variables, used in collection
        NATIVE=-6, // native c library call procedure wrapper
        CONST=-7, // const type

        // package management
        MODULE=-8, // module is the name of the current ssakura source file
        IMPORT=-9, // import the given module

        // control flow
        IF=-10, // if branch
        ELSE=-11, // else branch, must be paired with a if
        REPEAT=-12, // loop
        UNTIL=-13, // loop
        TIMES=-14, // loop
        RETURN=-15, // return a variable

        // operators
        NOT=-16, // boolean operator
        AND=-17, // boolean operator
        OR=-18, // boolean operator
        MOD=-19, // arithmetic operator, this is an exception, why not use %? fuck AP CSP

        // types
        TYPE_I8=-20, // signed 8bit integer
        TYPE_I16=-21, // signed 16bit integer
        TYPE_I32=-22, // signed 32bit integer
        TYPE_I64=-23, // signed 64bit integer
        TYPE_I128=-24, // signed 128bit integer
        TYPE_ISIZE=-25, // 64bit signed long, used for container length/size, with -1 not found flang
        TYPE_U8=-26, // unsigned 8bit integer
        TYPE_U16=-27, // unsigned 16bit integer
        TYPE_U32=-28, // unsigned 32bit integer
        TYPE_U64=-29, // unsigned 64bit integer
        TYPE_U128=-30, // unsigned 128bit integer
        TYPE_USIZE=-31, // 64bit unsigned long, used for container length/size
        TYPE_F32=-32, // 32bit floating type
        TYPE_F64=-33, // 64bit floating
        TYPE_BOOLEAN=-34, // boolean
        TYPE_STRING=-35, // string type
        TYPE_CHAR=-36, // char type

        // literals
        LITERAL_STRING=-37, // string literal
        LITERAL_CHAR=-38, // char literal

        // indicators
        IDENTIFIER = -39, // variable identifier
        NUMBER = -40, // numeric val/

        // typedef
        USE=-41, // give a alias name to a type

        // ?
        BRACE=-43, // {
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

    std::string numberVal;   // filled in if TOKEN_NUMBER
    std::string identifierVal;  // filled in if TOKEN_IDENTIFIER
};

#endif //SSAKURA_FRONTEND_LEXER_HPP
