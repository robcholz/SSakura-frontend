//
// Created by robcholz on 2/27/24.
//
#include "anemos/type/VariableDeclaration.hpp"

using namespace anemos;

VariableDeclaration::VariableDeclaration(std::string name, Type type)
    : name(std::move(name)), type(std::move(type)) {}