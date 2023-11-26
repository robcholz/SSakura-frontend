//
// Created by robcholz on 11/26/23.
//
#pragma once

#ifndef SSAKURA_FUNCTIONAST_HPP
#define SSAKURA_FUNCTIONAST_HPP


#include <memory>
#include <string>
#include <vector>
#include "ExprAST.hpp"

class FunctionAST {
public:
    explicit FunctionAST(const std::string& name,std::vector<std::string> arguments,std::unique_ptr<ExprAST> body);
private:
    std::string name;
    std::vector<std::string> arguments;
    std::unique_ptr<ExprAST> body;
};

#endif //SSAKURA_FUNCTIONAST_HPP
