//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LEXER_HPP
#define SSAKURA_FRONTEND_LEXER_HPP

#include <string>
#include <string_view>
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
        TYPE_F16=-32,
        TYPE_F32=-33, // 32bit floating type
        TYPE_F64=-34, // 64bit floating
        TYPE_BOOLEAN=-35, // boolean
        TYPE_STRING=-36, // string type
        TYPE_CHAR=-37, // char type

        // literals
        LITERAL_STRING=-38, // string literal
        LITERAL_CHAR=-39, // char literal

        // indicators
        IDENTIFIER = -40, // variable identifier
        NUMBER = -41, // numeric val/

        // typedef
        USE=-42, // give a alias name to a type

        // ?
        BRACE=-43, // {
    };

    Lexer();
    ~Lexer()=default;

    void readFile(const std::string& filename);
    void closeFile();

    std::string getToken();
    std::string getNumberVal() const;
    std::string getIdentifierVal() const;

private:
    char getNextChar();
    std::ifstream file;
    char lastChar;
    char currChar;

    std::string numberVal;   // filled in if TOKEN_NUMBER
    std::string identifierVal;  // filled in if TOKEN_IDENTIFIER

    inline static bool allOf(const std::string_view& str,bool(*condition_function)(char)){
        if (str.length() == 1)
            return condition_function(str[0]);
        for (const auto& ch: str) {
            if (condition_function(ch) != ' ')
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

    static bool isSpace(const std::string_view& str);
    static bool isSpace(char str);
    static bool isAlpha(const std::string_view& str);
    static bool isAlpha(char str);
    static bool isNum(const std::string_view& str);
    static bool isNum(char str);
    static bool isDigit(const std::string_view& str);
    static bool isDigit(char str);
};

#endif //SSAKURA_FRONTEND_LEXER_HPP
