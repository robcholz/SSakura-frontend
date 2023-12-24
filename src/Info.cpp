//
// Created by robcholz on 11/27/23.
//
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include "Info.hpp"


Info::Info(){
    this->llvmContext=std::make_unique<llvm::LLVMContext>();
    this->module=std::make_unique<llvm::Module>("My Cool JIT", *llvmContext);
    this->IRBuilder=std::make_unique<llvm::IRBuilder<>>(*llvmContext);
    this->functionPass=std::make_unique<llvm::legacy::FunctionPassManager>(module.get());

    //functionPass->add(llvm::createInstructionCombiningPass());
    //functionPass->add(llvm::createReassociatePass());
    //functionPass->add(llvm::createGVNPass());
    //functionPass->add(llvm::createCFGSimplificationPass());
    //functionPass->doInitialization();
}

Info& Info::getInstance() {
    static Info info;
    return info;
}

llvm::LLVMContext& Info::getLLVMContext() const{
    return *llvmContext;
}

llvm::IRBuilder<>& Info::getIRBuilder() const{
    return *IRBuilder;
}

llvm::Module& Info::getModule()const {
    return *module;
}

std::map<std::string, llvm::Value*>& Info::getNamedValues() {
    return namedValues;
}

llvm::legacy::FunctionPassManager& Info::getFunctionPass()const {
    return *functionPass;
}
