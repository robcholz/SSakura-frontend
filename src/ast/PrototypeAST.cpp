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

    static auto type2LLVMType = [&](const Type& type)-> llvm::Type* {
        if (type.isInteger()) {
            return llvm::IntegerType::get(context, type.getBitWidth());
        } else if (type.isFloat()) {
            if (type.getBitWidth() == 32) {
                return llvm::Type::getFloatTy(context);
            } else {
                return llvm::Type::getDoubleTy(context);
            }
        }
        return nullptr;
        // TODO implment more types
    };

    for (const auto& element: immutable_arguments) {
        if(auto converted_type=type2LLVMType(element.getType())) {
            params.push_back(converted_type);
        }
    }

    llvm::Type* return_type = type2LLVMType(returnType);

    llvm::FunctionType* function_type = llvm::FunctionType::get(return_type, params, false);
    llvm::Function* prototype = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name, module);
    size_t index = 0;
    for (auto& arg: prototype->args()) arg.setName(immutable_arguments[index++].getName());
    return prototype;
}
