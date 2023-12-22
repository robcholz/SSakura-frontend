//
// Created by robcholz on 12/22/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_COMPILER_HPP
#define SSAKURA_FRONTEND_COMPILER_HPP

#include "ElementaryType.hpp"
#include "Lexer.hpp"


class Compiler {
public:
    static void init() {
        ElementaryType::init();
        Lexer::init();
    }
};

#endif //SSAKURA_FRONTEND_COMPILER_HPP
