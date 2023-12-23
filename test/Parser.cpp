//
// Created by robcholz on 11/26/23.
//
#include <iostream>

#include <catch2/catch_all.hpp>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Value.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include "ast/FunctionAST.hpp"

#include "Parser.hpp"
#include "Info.hpp"
#include "Lexer.hpp"


int main() {
    ssa::init();
    Lexer lexer;
    lexer.readFile("/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/test/parserExample.txt");
    auto parser = Parser(&lexer);
    parser.getNextToken();
    bool flag = true;
    while (flag) {
        auto token = parser.getCurrentToken();
        if (token == "\xff") {
            flag = false;
        } else if (token == "EXTERN") {
            auto function = parser.parseExternExpr();
            function->codeGen()->print(llvm::errs());
            std::cout << ("parsed a function declration") << std::endl;
        } else if (token == "PROCEDURE") {
            auto function = parser.parseFunctionExpr();
            function->codeGen()->print(llvm::errs());
            std::cout << ("parsed a function definition") << std::endl;
        } else {
            auto function = parser.parseTopLevelExpr();
            function->codeGen()->print(llvm::errs());
            std::cout << ("parsed a top level expr") << std::endl;
        }
    }
    std::error_code EC;
    llvm::raw_fd_ostream OS("/Users/zhangjie/Documents/Code/CompletePrograms/SSakura-frontend/test/src.txt", EC);
    //llvm::WriteBitcodeToFile(Info::getInstance().getModule(), OS);
    //OS.flush();
    return 0;
}
