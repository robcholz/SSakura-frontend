//
// Created by robcholz on 2/19/24.
//
#include "ssa/ast/ExprAST.hpp"
#include "ssa/ast/BinaryExprAST.hpp"
#include "ssa/ast/BlockExprAST.hpp"
#include "ssa/ast/CallableExprAST.hpp"
#include "ssa/ast/FunctionAST.hpp"

#include "ssa/value/Value.hpp"
#include "ssa/type/Type.hpp"

#include "anemos/type/Value.hpp"
#include "anemos/type/Type.hpp"
#include "anemos/ast/ExpressionAST.hpp"

extern anemos::Value toAnemosValue(const ssa::Value& value);

extern anemos::Type toAnemosType(const ssa::Type& type);

extern std::unique_ptr<anemos::ExpressionAST> ast_visitor(const ssa::ExprAST* ast);