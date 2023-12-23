//
// Created by robcholz on 12/22/23.
//
#include "syntax/Checker.hpp"


Checker& Checker::getInstance() {
    static Checker checker;
    return checker;
}

const Lexer::Token& Checker::getNextVerifyThisToken(Parser* parser, ssa::Keyword keyword) {
    return getNextVerifyThisToken<ssa::Keyword>(parser, ErrorUnexpectedKeyword, keyword);
}

const Lexer::Token& Checker::getNextVerifyThisToken(Parser* parser, ssa::ReservedSymbol symbol) {
    return getNextVerifyThisToken<ssa::ReservedSymbol>(parser, ErrorUnexpectedSymbol, symbol);
}

const Lexer::Token& Checker::getNextVerifyNextToken(Parser* parser, ssa::Keyword keyword) {
    return getNextVerifyNextToken<ssa::Keyword>(parser, ErrorUnexpectedKeyword, keyword);
}

const Lexer::Token& Checker::getNextVerifyNextToken(Parser* parser, ssa::ReservedSymbol symbol) {
    return getNextVerifyNextToken<ssa::ReservedSymbol>(parser, ErrorUnexpectedSymbol, symbol);
}

const Lexer::Token& Checker::getNextVerifyNextToken(Parser* parser, const std::vector<ssa::ReservedSymbol>& symbols) {
    return getNextVerifyNextToken<ssa::ReservedSymbol>(parser, ErrorUnexpectedSymbol, symbols);
}

bool Checker::verifyCurrentToken(const Parser* parser, ssa::Keyword keyword,bool silence) {
    return verifyCurrentToken<ssa::Keyword>(parser, ErrorUnexpectedKeyword, keyword,silence);
}

bool Checker::verifyCurrentToken(const Parser* parser, ssa::ReservedSymbol symbol,bool silence) {
    return verifyCurrentToken<ssa::ReservedSymbol>(parser, ErrorUnexpectedSymbol, symbol,silence);
}

bool Checker::verifyEatCurrentToken(Parser* parser, ssa::Keyword keyword) {
    if (verifyCurrentToken(parser, keyword)) {
        parser->getNextToken();
        return true;
    }
    return false;
}

bool Checker::verifyEatCurrentToken(Parser* parser, ssa::ReservedSymbol symbol) {
    if (verifyCurrentToken(parser, symbol)) {
        parser->getNextToken();
        return true;
    }
    return false;
}
