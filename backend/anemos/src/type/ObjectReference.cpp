//
// Created by robcholz on 2/28/24.
//
#include <utility>

#include "anemos/type/ObjectReference.hpp"

using namespace anemos;

ObjectReference::ObjectReference(std::string name) : objectName(std::move(name)) {}