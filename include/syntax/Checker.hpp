//
// Created by robcholz on 12/20/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_CHECKER_HPP
#define SSAKURA_FRONTEND_CHECKER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <magic_enum/magic_enum.hpp>
#include <boost/format.hpp>

#include "Parser.hpp"


class Checker {
public:
    Checker(const Checker& other) = delete;

    Checker(Checker&& other) = delete;

    Checker& operator=(const Checker& other) = delete;

    Checker& operator=(Checker&& other) noexcept = delete;

    enum ErrorCode {
        ErrorUnexpectedSymbol,
        ErrorExpectedSymbol,
        ErrorUnexpectedKeyword,
    };

    static Checker& getInstance();

    static const Lexer::Token& getNextVerifyThisToken(Parser* parser, ssa::Keyword keyword);

    static const Lexer::Token& getNextVerifyThisToken(Parser* parser, ssa::ReservedSymbol symbol);

    static const Lexer::Token& getNextVerifyNextToken(Parser* parser, ssa::Keyword keyword);

    static const Lexer::Token& getNextVerifyNextToken(Parser* parser, ssa::ReservedSymbol symbol);

    static const Lexer::Token& getNextVerifyNextToken(Parser* parser, const std::vector<ssa::ReservedSymbol>& symbols);

    static bool verifyCurrentToken(const Parser* parser, ssa::Keyword token, bool silence = false);

    static bool verifyCurrentToken(const Parser* parser, ssa::ReservedSymbol symbol, bool silence = false);

    static bool verifyEatCurrentToken(Parser* parser, ssa::Keyword keyword);

    static bool verifyEatCurrentToken(Parser* parser, ssa::ReservedSymbol symbol);

private:
    Checker() = default;

    ~Checker() = default;

    inline static std::unordered_map<ErrorCode, std::string> errorCodeMap;

    inline static const auto getErrorHintMap = []()-> const std::unordered_map<ErrorCode, std::string>& {
        auto addItem = [&](ErrorCode item) {
            errorCodeMap.insert({item, std::string(magic_enum::enum_name(item)) + ": %s but found %s"});
        };
        for (const auto& element: magic_enum::enum_values<ErrorCode>()) {
            addItem(element);
        }
        return errorCodeMap;
    }();

    template<typename T>
    inline static void emitError(ErrorCode error, const T& expect, const T& found) {
        std::cout << boost::format(getErrorHintMap.at(error)) % ssa::to_string(expect)
                % ssa::to_string(found) << std::endl;
    }

    template<typename T>
    inline static bool verify(ErrorCode error, const T& expect, const Lexer::Token& token, bool silence) {
        if (token.is<T>()) {
            const auto& found = token.get<T>();
            if (expect != found) {
                if (!silence)
                    emitError(error, expect, found);
                return false;
            }
            return true;
        }
        return false;
    }

    template<typename T>
    inline static bool verify(ErrorCode error, const std::vector<T>& expects, const Lexer::Token& token) {
        if (token.is<T>()) {
            const auto& found = token.get<T>();
            for (const auto& element: expects) {
                if (element == found) {
                    return true;
                }
            }
            std::cout << boost::format(getErrorHintMap.at(error)) % ssa::to_string(found) << std::endl;
        }
        std::cout << boost::format(getErrorHintMap.at(error)) % "No Match" << std::endl;
        return false;
    }

    template<typename T>
    inline static const Lexer::Token& getNextVerifyNextToken(Parser* parser, ErrorCode error, const T& expect) {
        const Lexer::Token& token = parser->getNextToken();
        verify<T>(error, expect, token, false);
        return token;
    }

    template<typename T>
    inline static const Lexer::Token& getNextVerifyNextToken(Parser* parser, ErrorCode error, const std::vector<T>& expects) {
        const Lexer::Token& token = parser->getNextToken();
        verify<T>(error, expects, token);
        return token;
    }

    template<typename T>
    inline static const Lexer::Token& getNextVerifyThisToken(Parser* parser, ErrorCode error, const T& expect) {
        verify<T>(error, expect, parser->getCurrentToken(), false);
        return parser->getNextToken();
    }

    template<typename T>
    inline static bool verifyCurrentToken(const Parser* parser, ErrorCode error, const T& expect, bool silence) {
        return verify<T>(error, expect, parser->getCurrentToken(), silence);
    }
};

#endif //SSAKURA_FRONTEND_CHECKER_HPP
