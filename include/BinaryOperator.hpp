//
// Created by robcholz on 12/23/23.
//
#pragma once

#ifndef BINARYOPERATOR_HPP
#define BINARYOPERATOR_HPP

#include "Lexer.hpp"
#include "ReservedWords.hpp"


class BinaryOperator {
public:
    static ssa::BinaryOperator getOperator(const Lexer::Token& token) {
        if (token.isSymbol()) {
            const auto& symbol = token.getSymbol();
            if (symbol == ssa::ReservedSymbol::LABRAC)
                return ssa::BinaryOperator::LESS;
            if (symbol == ssa::ReservedSymbol::RABRAC)
                return ssa::BinaryOperator::GREATER;
            if (symbol == ssa::ReservedSymbol::PLUS)
                return ssa::BinaryOperator::ADD;
            if (symbol == ssa::ReservedSymbol::HYPEN)
                return ssa::BinaryOperator::MINUS;
            if (symbol == ssa::ReservedSymbol::ASTERISK)
                return ssa::BinaryOperator::MULTIPLE;
            if (symbol == ssa::ReservedSymbol::SLASH)
                return ssa::BinaryOperator::DIVISON;
            if (symbol == ssa::ReservedSymbol::EQUAL_SIGN)
                return ssa::BinaryOperator::EQUAL;
        }
        if (token.isKeyword()) {
            const auto& identifier = token.getKeyword();
            if (identifier == ssa::Keyword::MOD)
                return ssa::BinaryOperator::MOD;
            if (identifier == ssa::Keyword::AND)
                return ssa::BinaryOperator::AND;
            if (identifier == ssa::Keyword::NOT)
                return ssa::BinaryOperator::NOT;
            if (identifier == ssa::Keyword::OR)
                return ssa::BinaryOperator::OR;
        }
        return static_cast<ssa::BinaryOperator>(-1);
    }

    static int getPrecedence(const Lexer::Token& token) {
        return getPrecedence(getOperator(token));
    }

    static int getPrecedence(ssa::BinaryOperator binaryOperator) {
        switch (binaryOperator) {
            case ssa::BinaryOperator::LESS:
                return 10;
            case ssa::BinaryOperator::GREATER:
                return 10;
            case ssa::BinaryOperator::ADD:
                return 20;
            case ssa::BinaryOperator::MINUS:
                return 20;
            case ssa::BinaryOperator::MULTIPLE:
                return 30;
            case ssa::BinaryOperator::DIVISON:
                return 30;
            case ssa::BinaryOperator::MOD:
                return 30;
            case ssa::BinaryOperator::AND:
                return 40;
            case ssa::BinaryOperator::EQUAL:
                return 40;
            case ssa::BinaryOperator::NOT:
                return 40;
            case ssa::BinaryOperator::OR:
                return 40;
        }
        return -1;
    }
};

#endif //BINARYOPERATOR_HPP
