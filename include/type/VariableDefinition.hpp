//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_VARIABLEDEFINITION_HPP
#define SSAKURA_FRONTEND_VARIABLEDEFINITION_HPP

#include <string>

#include "type/Type.hpp"


class VariableDefinition : public Type {
public:
    VariableDefinition(const std::string& name, const std::string& type);

    std::string getName() const;
private:
    std::string typeName;
};

#endif //SSAKURA_FRONTEND_VARIABLEDEFINITION_HPP
