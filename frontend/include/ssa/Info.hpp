//
// Created by robcholz on 11/27/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_INFO_HPP
#define SSAKURA_FRONTEND_INFO_HPP

#include <map>
#include <memory>

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
/*
    llvm::LLVMContext& getLLVMContext() const;

    llvm::IRBuilder<>& getIRBuilder() const;

    llvm::Module& getModule() const;

    std::map<std::string, llvm::Value*>& getNamedValues();

    llvm::legacy::FunctionPassManager& getFunctionPass() const;
    */

private:
    Info();
};

#endif //SSAKURA_FRONTEND_INFO_HPP
