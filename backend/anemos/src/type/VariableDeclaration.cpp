//
// Created by robcholz on 2/27/24.
//
#include "anemos/type/VariableDeclaration.hpp"

using namespace anemos;

VariableDeclaration::VariableDeclaration(std::string name, Value value)
    : name(std::move(name)), value(std::move(value)) {}