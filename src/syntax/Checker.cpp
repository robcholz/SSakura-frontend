//
// Created by robcholz on 12/22/23.
//
#include <iostream>

#include <boost/format.hpp>

#include "syntax/Checker.hpp"


using namespace ssa;

Checker& Checker::getInstance() {
    static Checker checker;
    return checker;
}

bool Checker::check(ErrorCode error, const std::string_view& expect, const std::string_view& found) {
    if (expect != found) {
        std::cout << boost::format(getErrorHintMap.at(error)) % expect % found << std::endl;
        return false;
    }
    return true;
}

bool Checker::check(ErrorCode error, const std::vector<std::string_view>& expect, const std::string_view& found) {
    for (const auto& element: expect) {
        if (element == found) {
            return true;
        }
    }
    std::cout << boost::format(getErrorHintMap.at(error)) % "hi" % found << std::endl;
    return false;
}

std::string Checker::getNextVerifyThisToken(Parser* parser, const std::string& expect) {
    check(ErrorUnexpectedSymbol, expect, parser->getCurrentToken());
    return parser->getNextToken();
}

// TODO figure out this werid behavior
std::string Checker::getNextVerifyThisToken(Parser* parser, Keyword token) {
    std::string result{parser->getLexer()->getIdentifierVal()};
    check(ErrorUnexpectedKeyword, magic_enum::enum_name(token), result);
    return parser->getNextToken();
}

std::string Checker::getNextVerifyNextToken(Parser* parser, const std::string& expect) {
    std::string result{parser->getNextToken()};
    check(ErrorUnexpectedKeyword, expect, result);
    return result;
}

std::string Checker::getNextVerifyNextToken(Parser* parser, const std::vector<std::string_view>& expect) {
    std::string result{parser->getNextToken()};
    check(ErrorUnexpectedKeyword, expect, result);
    return result;
}

bool Checker::promiseCurrentToken(Parser* parser, Keyword token) {
    const auto res = parser->getLexer()->getIdentifierVal();
    return check(ErrorUnexpectedKeyword, magic_enum::enum_name(token), res);
}

bool Checker::promiseCurrentToken(Parser* parser, const std::string& token) {
    const auto res = parser->getLexer()->getIdentifierVal();
    return check(ErrorUnexpectedKeyword, token, res);
}

bool Checker::promiseEatCurrentToken(Parser* parser, Keyword token) {
    if (promiseCurrentToken(parser, token)) {
        parser->getNextToken();
        return true;
    }
    return false;
}

bool Checker::promiseEatCurrentToken(Parser* parser, const std::string& token) {
    if (promiseCurrentToken(parser, token)) {
        parser->getNextToken();
        return true;
    }
    return false;
}

void Checker::check(int result, ErrorCode error, const std::string& expect) {
    std::cout << boost::format(getErrorHintMap.at(error)) % expect % std::string(1, static_cast<char>(result)) << std::endl;
}
