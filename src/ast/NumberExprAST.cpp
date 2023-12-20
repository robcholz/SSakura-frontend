//
// Created by robcholz on 11/25/23.
//
#include <complex>

#include <llvm/IR/Constants.h>

#include "ast/NumberExprAST.hpp"
#include "Info.hpp"
#include "tools/Utilities.hpp"


NumberExprAST::NumberExprAST(const std::string &number)
    :constant(number){
}

llvm::Value* NumberExprAST::codeGen() {
    return constant.toLLVMConstant();
}
