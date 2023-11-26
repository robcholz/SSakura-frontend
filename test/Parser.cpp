//
// Created by robcholz on 11/26/23.
//
#include <catch2/catch_all.hpp>
#include "Parser.hpp"


TEST_CASE("Parser Assertion") {
    Lexer lexer;
    lexer.readFile("/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/test/parserExample.txt");
    auto parser = Parser(&lexer);
    parser.getNextToken();
    bool flag=true;
    while (flag) {
        switch (parser.getCurrentToken()) {
            case (int)Lexer::Token::TOK_EOF:
                flag=false;
            case (int)Lexer::Token::PROCEDURE: {
                parser.parseFunctionExpr();
                INFO("parsed a function definition");
                break;
            }
            default: {
                parser.parseTopLevelExpr();
                INFO("parsed a top level expr");
                break;
            }
        }
    }
}
