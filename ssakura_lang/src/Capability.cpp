//
// Created by robcholz on 2/19/24.
//
#include "Capability.hpp"
#include <algorithm>
#include "anemos/ast/BinaryOperatorExpressionAST.hpp"
#include "anemos/ast/BlockExpressionAST.hpp"
#include "anemos/ast/FunctionExpressionAST.hpp"
#include "anemos/ast/IfExpressionAST.hpp"
#include "anemos/ast/NumberExpressionAST.hpp"
#include "anemos/ast/ObjectExpressionAST.hpp"

#include "ssa/ast/IfExprAST.hpp"
#include "ssa/ast/NumberExprAST.hpp"
#include "ssa/ast/VariableExprAST.hpp"
#include "ssa/value/Value.hpp"

anemos::Value toAnemosValue(const ssa::Value& value) {
  if (value.getType().isPrimitive()) {
    switch (value.getType().getPrimitive().value()) {
      case ssa::Primitive::I8: {
        return anemos::Value::makeSignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::I8>>()
                .value(),
            anemos::Primitive::I8);
      }
      case ssa::Primitive::I16: {
        return anemos::Value::makeSignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::I16>>()
                .value(),
            anemos::Primitive::I16);
      }
      case ssa::Primitive::I32: {
        return anemos::Value::makeSignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::I32>>()
                .value(),
            anemos::Primitive::I32);
      }
      case ssa::Primitive::I64: {
        return anemos::Value::makeSignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::I64>>()
                .value(),
            anemos::Primitive::I64);
      }
      case ssa::Primitive::ISIZE: {
        return anemos::Value::makeIsize(
            value
                .getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::ISIZE>>()
                .value());
      }
      case ssa::Primitive::U8: {
        return anemos::Value::makeUnsignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::U8>>()
                .value(),
            anemos::Primitive::U8);
      }
      case ssa::Primitive::U16: {
        return anemos::Value::makeUnsignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::U16>>()
                .value(),
            anemos::Primitive::U16);
      }
      case ssa::Primitive::U32: {
        return anemos::Value::makeUnsignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::U32>>()
                .value(),
            anemos::Primitive::U32);
      }
      case ssa::Primitive::U64: {
        return anemos::Value::makeUnsignedInteger(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::U64>>()
                .value(),
            anemos::Primitive::U64);
      }
      case ssa::Primitive::USIZE: {
        return anemos::Value::makeUsize(
            value
                .getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::USIZE>>()
                .value());
      }
      case ssa::Primitive::F32: {
        return anemos::Value::makeF32(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::F32>>()
                .value());
      }
      case ssa::Primitive::F64: {
        return anemos::Value::makeF64(
            value.getValue<ssa::primitiveTypeEnumToType<ssa::Primitive::F64>>()
                .value());
      }
      case ssa::Primitive::VOID: {
        // TODO
        break;
      }
      case ssa::Primitive::NONE: {
        // TODO
        break;
      }
    }
  }  // primitive type implementation
  // TODO
  return anemos::Value::makeObjectReference(anemos::ObjectReference());
}

anemos::Type toAnemosType(const ssa::Type& type) {
  if (type.isPrimitive()) {
    switch (type.getPrimitive().value()) {
      case ssa::Primitive::I8:
        return anemos::Primitive::I8;
      case ssa::Primitive::I16:
        return anemos::Primitive::I16;
      case ssa::Primitive::I32:
        return anemos::Primitive::I32;
      case ssa::Primitive::I64:
        return anemos::Primitive::I64;
      case ssa::Primitive::ISIZE:
        return anemos::Primitive::ISIZE;
      case ssa::Primitive::U8:
        return anemos::Primitive::U8;
      case ssa::Primitive::U16:
        return anemos::Primitive::U16;
      case ssa::Primitive::U32:
        return anemos::Primitive::U32;
      case ssa::Primitive::U64:
        return anemos::Primitive::U64;
      case ssa::Primitive::USIZE:
        return anemos::Primitive::USIZE;
      case ssa::Primitive::F32:
        return anemos::Primitive::F32;
      case ssa::Primitive::F64:
        return anemos::Primitive::F64;
      case ssa::Primitive::VOID:
        return anemos::Primitive::VOID;
      case ssa::Primitive::NONE:
        std::terminate();  // TODO
    }
  }
  // TODO
  return anemos::Primitive::U8;
}

std::unique_ptr<anemos::ExpressionAST> ast_visitor(const ssa::ExprAST* ast) {
  switch (ast->getType()) {
    case ssa::ExprAST::Type::BINARY_EXPR: {
      auto binary_ast = dynamic_cast<const ssa::BinaryExprAST*>(ast);
      anemos::BinaryOperatorExpressionAST::BinaryOperatorEnum
          binary_operator_enum;
      switch (binary_ast->getOperatorType()) {
        case ssa::BinaryOperator::ADD:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::ADD;
          break;
        case ssa::BinaryOperator::SUBTRACT:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::SUBTRACT;
          break;
        case ssa::BinaryOperator::MULTIPLE:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::MULTIPLE;
          break;
        case ssa::BinaryOperator::DIVISION:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::DIVISION;
          break;
        case ssa::BinaryOperator::MOD:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::MOD;
          break;
        case ssa::BinaryOperator::GREATER:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::GREATER;
          break;
        case ssa::BinaryOperator::LESS:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::LESS;
          break;
        case ssa::BinaryOperator::EQUAL:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::EQUAL;
          break;
        case ssa::BinaryOperator::NOT:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::NOT;
          break;
        case ssa::BinaryOperator::AND:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::AND;
          break;
        case ssa::BinaryOperator::OR:
          binary_operator_enum = anemos::BinaryOperatorExpressionAST::OR;
          break;
      }
      auto lhs = ast_visitor(&binary_ast->getLHS());
      auto rhs = ast_visitor(&binary_ast->getRHS());
      return std::make_unique<anemos::BinaryOperatorExpressionAST>(
          binary_operator_enum, std::move(lhs), std::move(rhs));
    }
    case ssa::ExprAST::Type::BLOCK_EXPR: {
      auto block_ast = dynamic_cast<const ssa::BlockExprAST*>(ast);
      std::vector<std::unique_ptr<anemos::ExpressionAST>> expressions;
      std::for_each(block_ast->begin(), block_ast->end(),
                    [&expressions](const auto& expr) {
                      expressions.push_back(ast_visitor(expr.get()));
                    });
      return std::make_unique<anemos::BlockExpressionAST>(
          std::move(expressions));
    }
    case ssa::ExprAST::Type::CALLABLE_EXPR: {
      auto callable_ast = dynamic_cast<const ssa::CallableExprAST*>(ast);

      break;
    }
    case ssa::ExprAST::Type::FUNCTION_EXPR: {
      auto function_ast = dynamic_cast<const ssa::FunctionAST*>(ast);
      auto& prototype = function_ast->getPrototype();
      auto anemos_function = std::make_unique<anemos::FunctionExpressionAST>();

      anemos_function->addName(prototype.getName());
      anemos_function->addReturn(toAnemosType(prototype.getReturnType()));

      anemos::Parameter parameter;
      std::for_each(prototype.getArguments().begin(),
                    prototype.getArguments().end(),
                    [&parameter](const auto& param) {
                      parameter.add(anemos::VariableDeclaration(
                          param->getName(), toAnemosValue(param->getValue())));
                    });
      anemos_function->addParameter(std::move(parameter));
      auto body = ast_visitor(&function_ast->getBody());
      anemos_function->addBody(std::move(body));
      return std::move(anemos_function);
    }
    case ssa::ExprAST::Type::IF_EXPR: {
      auto if_ast = dynamic_cast<const ssa::IfExprAST*>(ast);
      auto condition = ast_visitor(&if_ast->getCondition());
      auto then_branch = ast_visitor(&if_ast->getThenBranch());
      auto raw_else_branch = if_ast->getElseBranch();
      std::unique_ptr<anemos::ExpressionAST> else_branch = nullptr;
      if (raw_else_branch.has_value())
        else_branch = ast_visitor(&raw_else_branch->get());
      return std::make_unique<anemos::IfExpressionAST>(
          std::move(condition), std::move(then_branch), std::move(else_branch));
    }
    case ssa::ExprAST::Type::NUMBER_EXPR: {
      auto number_ast = dynamic_cast<const ssa::NumberExprAST*>(ast);
      return std::make_unique<anemos::NumberExpressionAST>(
          toAnemosValue(number_ast->getNumber()));
    }
    case ssa::ExprAST::Type::REPEAT_EXPR: {
      break;
    }
    case ssa::ExprAST::Type::VARIABLE_EXPR: {
      auto variable_ast = dynamic_cast<const ssa::VariableExprAST*>(ast);
      return std::make_unique<anemos::ObjectExpressionAST>(
          anemos::ObjectReference(variable_ast->getName()));
    }
  }
  // silent the warning
  return {};
}
