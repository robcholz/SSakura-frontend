//
// Created by robcholz on 11/27/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_INFO_HPP
#define SSAKURA_FRONTEND_INFO_HPP

#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>


namespace llvm {
    class Value;
    class LLVMContext;
}

class Info {
public:
    Info(const Info& other) = delete;

    Info(Info&& other) noexcept = delete;

    Info& operator=(const Info& other) = delete;

    Info& operator=(Info&& other) noexcept = delete;

    static Info& getInstance();

    llvm::LLVMContext& getLLVMContext();
    llvm::IRBuilder<>& getIRBuilder();
    llvm::Module& getModule();
    std::map<std::string,llvm::Value*>& getNamedValues();
    llvm::legacy::FunctionPassManager& getFunctionPass();

private:
    Info();

    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> IRBuilder;
    llvm::Module module;
    llvm::legacy::FunctionPassManager functionPass;
    std::map<std::string, llvm::Value*> namedValues;
};

#endif //SSAKURA_FRONTEND_INFO_HPP
