//
// Created by robcholz on 12/19/23.
//
#include "rule/TypeName.hpp"

TypeName::TypeName(const std::string& name, const std::string& type)
    :Type(type){
    this->typeName=name;
}

std::string TypeName::getName() const {
    return typeName;
}