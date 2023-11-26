//
// Created by robcholz on 11/26/23.
//
#include "ast/FunctionAST.hpp"


FunctionAST::FunctionAST(const std::string& name, std::vector<std::string> arguments, std::unique_ptr<ExprAST> body) {
    this->name=name;
    this->arguments=std::move(arguments);
    this->body=std::move(body);
}
