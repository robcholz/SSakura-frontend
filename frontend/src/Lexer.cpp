//
// Created by robcholz on 11/25/23.
//
#include "ssa/Lexer.hpp"
#include <spdlog/spdlog.h>
#include <magic_enum/magic_enum.hpp>

using namespace ssa;

Lexer::Lexer() {
  this->lastChar = ' ';
  this->currChar = EOF;
  this->token = Token{};
}

void Lexer::readFile(std::string_view filename) {
  file.open(filename);
  while (!file.is_open()) {
  }
}

void Lexer::closeFile() {
  file.close();
}

ssa::s_char_t Lexer::getNextChar() {
  s_char_t ch;
  file.get(ch);
  return ch;
}

Token Lexer::getToken() {
  if (tokenBuffer.empty())
    return getNextToken();
  Token tk = tokenBuffer.front();
  tokenBuffer.pop_front();
  return std::move(tk);
}

Token Lexer::lookAhead() {
  return lookAhead(1);
}

Token Lexer::lookAhead(std::size_t size) {
  if (tokenBuffer.size() < size)
    for (std::ptrdiff_t i = 0;
         i < static_cast<std::ptrdiff_t>(size) - tokenBuffer.size(); i++)
      tokenBuffer.push_back(getNextToken());
  return tokenBuffer.front();
}

Token Lexer::getNextToken() {
  while (isSpace(lastChar)) {
    lastChar = getNextChar();
  }  // ignore space

  if (isAlpha(lastChar)) {
    pattern.clear();
    // TODO make sure a number literal format
    while (isNum(lastChar)) {
      pattern.push_back(lastChar);
      lastChar = getNextChar();
    }
    // TokenCategory::KEYWORD
    if (contains<Keyword>(pattern)) {
      token.category = TokenCategory::KEYWORD;
      token.tokens = from_string<Keyword>(pattern).value();
      return token;
    } else {
      token.category = TokenCategory::IDENTIFIER;
      token.tokens = pattern;
      return token;
    }
  }  // string

  // TokenCategory::LITERAL
  if (isDigit(lastChar) || equals(lastChar, Symbol::DOT)) {
    token.category = TokenCategory::LITERAL;
    pattern.clear();
    while (isDigit(lastChar) || equals(lastChar, Symbol::DOT)) {
      pattern.push_back(lastChar);
      lastChar = getNextChar();
    }
    token.tokens = pattern;
    return token;
  }

  // comments
  if (equals(lastChar, Symbol::HASHTAG)) {
    do
      lastChar = getNextChar();
    while (!equals(lastChar, Symbol::RETURN) &&
           !equals(lastChar, Symbol::EOF_FLAG) &&
           !equals(lastChar, Symbol::CARRIAGE_RETURN));
    if (!equals(lastChar, Symbol::EOF_FLAG)) {
      return getToken();
    }
  }

  if (contains<Symbol>(lastChar)) {
    token.category = TokenCategory::SYMBOL;
    pattern = lastChar;
    token.tokens = static_cast<Symbol>(lastChar);
  }
  if (equals(lastChar, Symbol::EOF_FLAG)) {
    token.category = TokenCategory::EOF_TERMINATOR;
  }

  currChar = lastChar;
  lastChar = getNextChar();

  // TODO fix this
  std::string result;
  result = currChar;
  return token;
}
