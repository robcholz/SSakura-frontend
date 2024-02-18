//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ADAPTERREGISTRY_HPP
#define SSAKURA_FRONTEND_ADAPTERREGISTRY_HPP

#include "ASTAdapter.hpp"
#include "ArithmeticOperationAdapter.hpp"

namespace ssa {
class AdapterRegistry {
 public:
  AdapterRegistry() = delete;
  ~AdapterRegistry() = delete;
  AdapterRegistry& operator=(AdapterRegistry&) = delete;

 protected:
  static void registerEqualityOperationCallback(
      decltype(ArithmeticOperationAdapter::equalityCallback) callback) {
    ArithmeticOperationAdapter::equalityCallback = std::move(callback);
  }

  static void registerGreaterThanOperationCallback(
      decltype(ArithmeticOperationAdapter::greaterThanCallback) callback) {
    ArithmeticOperationAdapter::greaterThanCallback = std::move(callback);
  }

  static void registerLessThanOperationCallback(
      decltype(ArithmeticOperationAdapter::lessThanCallback) callback) {
    ArithmeticOperationAdapter::lessThanCallback = std::move(callback);
  }

  static void registerBoolAndOperationCallback(
      decltype(ArithmeticOperationAdapter::boolAndCallback) callback) {
    ArithmeticOperationAdapter::boolAndCallback = std::move(callback);
  }

  static void registerBoolOrOperationCallback(
      decltype(ArithmeticOperationAdapter::boolOrCallback) callback) {
    ArithmeticOperationAdapter::boolOrCallback = std::move(callback);
  }

  static void registerBoolNotOperationCallback(
      decltype(ArithmeticOperationAdapter::boolNotCallback) callback) {
    ArithmeticOperationAdapter::boolNotCallback = std::move(callback);
  }

  static void registerModulusOperationCallback(
      decltype(ArithmeticOperationAdapter::modulusCallback) callback) {
    ArithmeticOperationAdapter::modulusCallback = std::move(callback);
  }

  static void registerAddOperationCallback(
      decltype(ArithmeticOperationAdapter::addCallback) callback) {
    ArithmeticOperationAdapter::addCallback = std::move(callback);
  }

  static void registerSubtractOperationCallback(
      decltype(ArithmeticOperationAdapter::subtractCallback) callback) {
    ArithmeticOperationAdapter::subtractCallback = std::move(callback);
  }

  static void registerMultipleOperationCallback(
      decltype(ArithmeticOperationAdapter::multipleCallback) callback) {
    ArithmeticOperationAdapter::multipleCallback = std::move(callback);
  }

  static void registerDivisionOperationCallback(
      decltype(ArithmeticOperationAdapter::divisionCallback) callback) {
    ArithmeticOperationAdapter::divisionCallback = std::move(callback);
  }

  static void registerBlockExprCallback(
      decltype(ASTAdapter::blockExprCallback) callback) {
    ASTAdapter::blockExprCallback = std::move(callback);
  }

  static void registerIfExprCallback(
      decltype(ASTAdapter::ifExprCallback) callback) {
    ASTAdapter::ifExprCallback = std::move(callback);
  }

  static void registerCallableExprCallback(
      decltype(ASTAdapter::callableExprCallback) callable) {
    ASTAdapter::callableExprCallback = std::move(callable);
  }

  static void registerFunctionExprCallback(
      decltype(ASTAdapter::functionExprCallback) callable) {
    ASTAdapter::functionExprCallback = std::move(callable);
  }

  static void registerRepeatExprCallback(
      decltype(ASTAdapter::repeatExprCallback) callable) {
    ASTAdapter::repeatExprCallback = std::move(callable);
  }

  static void registerPrototypeExprCallback(
      decltype(ASTAdapter::prototypeExprCallback) callable) {
    ASTAdapter::prototypeExprCallback = std::move(callable);
  }

  static void registerNumberExprCallback(
      decltype(ASTAdapter::numberExprCallback) callable) {
    ASTAdapter::numberExprCallback = std::move(callable);
  }

  static void registerVariableExprCallback(
      decltype(ASTAdapter::variableExprCallback) callable) {
    ASTAdapter::variableExprCallback = std::move(callable);
  }
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_ADAPTERREGISTRY_HPP
