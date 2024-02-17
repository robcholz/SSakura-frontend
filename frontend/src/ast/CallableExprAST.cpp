//
// Created by robcholz on 11/25/23.
//
#include "ast/CallableExprAST.hpp"
#include "Info.hpp"

using namespace ssa;

CallableExprAST::CallableExprAST(
    const std::string& callable,
    std::vector<std::unique_ptr<ExprAST>> arguments) {
  this->callable = callable;
  this->arguments = std::move(arguments);
}

Value CallableExprAST::codeGen() {

}
