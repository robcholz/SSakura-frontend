//
// Created by robcholz on 11/28/23.
//
#pragma once

#ifndef SSAKURA_PROTOTYPEAST_HPP
#define SSAKURA_PROTOTYPEAST_HPP

#include <string>
#include <vector>

#include "rule/ParameterList.hpp"
#include "../type/Type.hpp"


namespace llvm {
    class Function;
}

class PrototypeAST {
public:
    PrototypeAST(const std::string& name,
                 std::unique_ptr<ParameterList> arguments,
                 Type returnType);

    std::string getName() const;

    const Type& getReturnType() const;

    llvm::Function* codeGen();

private:
    std::string name;
    std::unique_ptr<ParameterList> arguements;
    Type returnType;
};

#endif //SSAKURA_PROTOTYPEAST_HPP
