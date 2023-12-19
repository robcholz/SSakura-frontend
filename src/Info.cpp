//
// Created by robcholz on 11/27/23.
//
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include "Info.hpp"


Info::Info()
    : IRBuilder(llvmContext),
      module("My Cool JIT", llvmContext), // TODO incorrect order might cause segfault
      functionPass(&module) {
    //functionPass.add(llvm::createInstructionCombiningPass());
    //functionPass.add(llvm::createReassociatePass());
    //functionPass.add(llvm::createGVNPass());
    //functionPass.add(llvm::createCFGSimplificationPass());
    //functionPass.doInitialization();
}

Info& Info::getInstance() {
    static Info info;
    return info;
}

llvm::LLVMContext& Info::getLLVMContext() {
    return llvmContext;
}

llvm::IRBuilder<>& Info::getIRBuilder() {
    return IRBuilder;
}

llvm::Module& Info::getModule() {
    return module;
}

std::map<std::string, llvm::Value*>& Info::getNamedValues() {
    return namedValues;
}

llvm::legacy::FunctionPassManager& Info::getFunctionPass() {
    return functionPass;
}
