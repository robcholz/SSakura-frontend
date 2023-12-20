//
// Created by robcholz on 12/19/23.
//
#include "type/VariableDefinition.hpp"


VariableDefinition::VariableDefinition(const std::string& name, const std::string& type)
    : ::Type(type){
    this->typeName=name;
}

std::string VariableDefinition::getName() const {
    return typeName;
}