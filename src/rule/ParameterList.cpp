//
// Created by robcholz on 12/19/23.
//
#include "rule/ParameterList.hpp"


void ParameterList::add(std::unique_ptr<VariableDefinition> type) {
    parameters.push_back(std::move(type));
}

size_t ParameterList::size() const {
    return parameters.size();
}

std::vector<VariableDefinition> ParameterList::getParameters() const {
    std::vector<VariableDefinition> params;
    for(const auto& element:parameters) {
        params.push_back(*element);
    }
    return std::move(params);
}
