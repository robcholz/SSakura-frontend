//
// Created by robcholz on 11/25/23.
//
#include <llvm/IR/Function.h>
#include "ast/CallableExprAST.hpp"
#include "Info.hpp"


CallableExprAST::CallableExprAST(const std::string& callable, std::vector<std::unique_ptr<ExprAST>> arguments) {
    this->callable=callable;
    this->arguments=std::move(arguments);
}

llvm::Value* CallableExprAST::codeGen() {
    llvm::Function* callee = Info::getInstance().getModule().getFunction(callable);
    std::vector<llvm::Value*> args;
    args.reserve(arguments.size());
    for (const auto& amp  : arguments) {
        args.push_back(amp->codeGen());
    }
    return Info::getInstance().getIRBuilder().CreateCall(callee, args, "calltmp");
}

