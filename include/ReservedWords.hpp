//
// Created by robcholz on 12/22/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_RESERVEDWORDS_HPP
#define SSAKURA_FRONTEND_RESERVEDWORDS_HPP


namespace ssa {
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
        AT='@', // annotation
        HASHTAG='#', // comment
    };

    enum class Elementary {
        I8,
        I16,
        I32,
        I64,
        I128,
        ISIZE,
        U8,
        U16,
        U32,
        U64,
        U128,
        USIZE,
        F16,
        F32,
        F64,
    };
}

#endif //SSAKURA_FRONTEND_RESERVEDWORDS_HPP
