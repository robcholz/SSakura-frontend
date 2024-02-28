//
// Created by robcholz on 2/19/24.
//
#include "anemos/ast/NumberExpressionAST.hpp"

using namespace anemos;

NumberExpressionAST::NumberExpressionAST(anemos::Value val): value(std::move(val)){

}

void NumberExpressionAST::execute() {

}