//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_PARAMETERLIST_HPP
#define SSAKURA_FRONTEND_PARAMETERLIST_HPP

#include <memory>
#include <vector>

#include "TypeName.hpp"


class ParameterList {
public:
    void add(std::unique_ptr<TypeName> type);
    size_t size() const;

    // return a copy of parameters
    std::vector<TypeName> getParameters() const ;

    static ParameterList emptyParamList() {
        return ParameterList{};
    }
private:
    std::vector<std::unique_ptr<TypeName>> parameters{};
};

#endif //SSAKURA_FRONTEND_PARAMETERLIST_HPP
