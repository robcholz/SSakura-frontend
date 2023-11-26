//
// Created by robcholz on 11/25/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLEEXPRAST_HPP
#define SSAKURA_FRONTEND_VARIABLEEXPRAST_HPP

#include <string>
#include "ExprAST.hpp"


class VariableExprAST:public ExprAST {
public:
    explicit VariableExprAST(const std::string& name);
private:
    std::string name;
};

#endif //SSAKURA_FRONTEND_VARIABLEEXPRAST_HPP
