//
// Created by robcholz on 12/19/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ELEMENTARYTYPE_HPP
#define SSAKURA_FRONTEND_ELEMENTARYTYPE_HPP

#include <string>
#include <unordered_map>

#include "Info.hpp"
#include "ReservedWords.hpp"


class ElementaryType {
public:
    static void init();

    static uint64_t getBitwidth(ssa::Elementary type);

    inline static ssa::Elementary toElementaryType(const std::string& type) {
        return elementMap_s2e.at(type);
    }

    inline static std::string to_string(ssa::Elementary type) {
        return elementMap_e2s.at(type);
    }

private:
    // TODO use fixed-container
    inline static std::unordered_map<std::string, ssa::Elementary> elementMap_s2e;
    inline static std::unordered_map<ssa::Elementary, std::string> elementMap_e2s;
};


#endif //SSAKURA_FRONTEND_ELEMENTARYTYPE_HPP
