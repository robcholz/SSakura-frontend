//
// Created by robcholz on 12/20/23.
//
#pragma once

#ifndef SSAKURA_FRONTEND_CHECKER_HPP
#define SSAKURA_FRONTEND_CHECKER_HPP

#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>

#include <magic_enum/magic_enum.hpp>

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

    static bool check(ErrorCode error, const std::string_view& expect, const std::string_view& found);

    static bool check(ErrorCode error, const std::vector<std::string_view>& expect, const std::string_view& found);

    static std::string getNextVerifyThisToken(Parser* parser, const std::string& expect);

    static std::string getNextVerifyThisToken(Parser* parser, Lexer::Token token);

    static std::string getNextVerifyNextToken(Parser* parser, const std::string& expect);

    static std::string getNextVerifyNextToken(Parser* parser, const std::vector<std::string_view>& expect);

    static bool promiseCurrentToken(Parser* parser, Lexer::Token token);

    static bool promiseCurrentToken(Parser* parser, const std::string& token);

    static bool promiseEatCurrentToken(Parser* parser,Lexer::Token token);

    static bool promiseEatCurrentToken(Parser* parser,const std::string& token);

    static void check(int result, ErrorCode error, const std::string& expect);

private:
    Checker() = default;

    inline static std::unordered_map<ErrorCode, std::string> errorCodeMap;

    inline static auto getErrorHintMap = []()-> std::unordered_map<ErrorCode, std::string> {
        auto addItem = [&](ErrorCode item) {
            errorCodeMap.insert({item, std::string(magic_enum::enum_name(item)) + ": %s but found %s"});
        };
        for (const auto& element: magic_enum::enum_values<ErrorCode>()) {
            addItem(element);
        }
        return errorCodeMap;
    }();
};

#endif //SSAKURA_FRONTEND_CHECKER_HPP
