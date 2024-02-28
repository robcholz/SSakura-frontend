//
// Created by robcholz on 2/28/24.
//
#include <algorithm>
#include "anemos/ast/ObjectExpressionAST.hpp"

using namespace anemos;

ObjectExpressionAST::ObjectExpressionAST(ObjectReference objectReference)
    : objectReference(std::move(objectReference)) {}

void ObjectExpressionAST::execute() {

}