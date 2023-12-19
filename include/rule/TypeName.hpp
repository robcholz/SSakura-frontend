//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_TYPENAME_HPP
#define SSAKURA_FRONTEND_TYPENAME_HPP

#include <string>

#include "Type.hpp"


class TypeName : public Type {
public:
    TypeName(const std::string& name, const std::string& type);

    std::string getName() const;
private:
    std::string typeName;
};

#endif //SSAKURA_FRONTEND_TYPENAME_HPP
