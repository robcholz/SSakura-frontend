//
// Created by robcholz on 11/25/23.
//
#include "ast/VariableExprAST.hpp"
#include "Info.hpp"


VariableExprAST::VariableExprAST(const std::string& name): name(name) {
}

llvm::Value* VariableExprAST::codeGen() {
    return Info::getInstance().getNamedValues().at(name);
}
