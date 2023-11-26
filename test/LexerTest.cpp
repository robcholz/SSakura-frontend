//
// Created by robcholz on 11/25/23.
//
#include <catch2/catch_all.hpp>
#include "Lexer.hpp"


TEST_CASE("Lexer Test Assertion") {
    Lexer lexer;
    lexer.readFile("/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/test/function.ssa");

    SECTION("Parse Token") {
        std::ofstream file;
        file.open("/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/test/output.txt");
        char ch = ' ';

        while (ch != EOF) {
            file << ch;
            ch = lexer.getToken();
        }
        file.close();
    }
    lexer.closeFile();
}
