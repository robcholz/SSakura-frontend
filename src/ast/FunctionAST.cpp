//
// Created by robcholz on 11/26/23.
//
#include <llvm/IR/Verifier.h>
#include "ast/ExprAST.hpp"
#include "ast/FunctionAST.hpp"
#include "ast/ProtoTypeAST.hpp"
#include "Info.hpp"


FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body) {
    this->prototype = std::move(prototype);
    this->body = std::move(body);
}

llvm::Value* FunctionAST::codeGen() {
    auto& context = Info::getInstance().getLLVMContext();
    const auto& module = Info::getInstance().getModule();
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& namedValues = Info::getInstance().getNamedValues();

    llvm::Function* function = module.getFunction(prototype->getName());
    if (!function)
        function = prototype->codeGen();
    if (!function)
        return nullptr;
    llvm::BasicBlock* basic_block= llvm::BasicBlock::Create(context, "entry", function);
    ir_builder.SetInsertPoint(basic_block);
    namedValues.clear();
    for (auto& arg: function->args()) {
        namedValues[std::string(arg.getName())] = &arg;
    }
    llvm::Value* ret_val = body->codeGen();
    if (!ret_val) {
        function->eraseFromParent();
        return nullptr;
    }
    ir_builder.CreateRet(ret_val);
    verifyFunction(*function);
    Info::getInstance().getFunctionPass().run(*function);
    return function;
}
