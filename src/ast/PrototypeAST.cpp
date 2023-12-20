//
// Created by robcholz on 11/28/23.
//
#include <llvm/IR/Function.h>
#include "ast/ProtoTypeAST.hpp"
#include "Info.hpp"

PrototypeAST::PrototypeAST(const std::string& name,
                           std::unique_ptr<ParameterList> arguments,
                           Type returnType)
                               :returnType(std::move(returnType)){
    this->name = name;
    this->arguements = std::move(arguments);
}

std::string PrototypeAST::getName() {
    return name;
}

llvm::Function* PrototypeAST::codeGen() {
    auto& context = Info::getInstance().getLLVMContext();
    auto& module = Info::getInstance().getModule();

    std::vector<llvm::Type*> params;
    const auto immutable_arguments = arguements->getParameters();

    params.reserve(arguements->size());

    for (const auto& element: immutable_arguments) {
        if(auto converted_type=element.toLLVMType()) {
            params.push_back(converted_type);
        }
    }

    llvm::Type* return_type = this->returnType.toLLVMType();

    llvm::FunctionType* function_type = llvm::FunctionType::get(return_type, params, false);
    llvm::Function* prototype = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name, module);
    size_t index = 0;
    for (auto& arg: prototype->args()) arg.setName(immutable_arguments[index++].getName());
    return prototype;
}
