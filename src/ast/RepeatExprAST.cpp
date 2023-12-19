//
// Created by robcholz on 11/28/23.
//
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include "ast/RepeatExprAST.hpp"
#include "Info.hpp"


RepeatExprAST::RepeatExprAST(const Type repeatType, std::unique_ptr<ExprAST> conditionExpr, std::unique_ptr<ExprAST> bodyExpr) {
    this->repeatType = repeatType;
    this->conditionExpr = std::move(conditionExpr);
    this->bodyExpr = std::move(bodyExpr);
}

llvm::Value* RepeatExprAST::codeGen() {
    auto& context = Info::getInstance().getLLVMContext();
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& named_values = Info::getInstance().getNamedValues();

    if (this->repeatType == Type::REPEAT_UNTIL) {
        llvm::Function* function = ir_builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* loop_block = llvm::BasicBlock::Create(context, "loop", function);
        ir_builder.CreateBr(loop_block);
        ir_builder.SetInsertPoint(loop_block);
        llvm::Value* iteration = conditionExpr->codeGen();
        if (!iteration)
            return nullptr;
        llvm::BasicBlock* after_block = llvm::BasicBlock::Create(context, "afterloop", function);
        // Convert condition to a bool by comparing non-equal to 0.
        iteration = ir_builder.CreateICmpNE(iteration, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0), "loopcond");
        ir_builder.CreateCondBr(iteration, loop_block, after_block);
        ir_builder.SetInsertPoint(after_block);
        if (!bodyExpr->codeGen())
            return nullptr;
        return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(context));
    } else {
        llvm::Value* numIterations = conditionExpr->codeGen();
        if (!numIterations)
            return nullptr;
        llvm::Function* TheFunction = ir_builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* LoopBB = llvm::BasicBlock::Create(context, "loop", TheFunction);
        ir_builder.CreateBr(LoopBB);
        ir_builder.SetInsertPoint(LoopBB);
        llvm::Type* unsignedLongType = ir_builder.getInt64Ty();
        llvm::AllocaInst* counterVariable = ir_builder.CreateAlloca(unsignedLongType);
        ir_builder.CreateStore(llvm::ConstantInt::get(unsignedLongType, 0), counterVariable);
        // Create the condition check: counter < numIterations
        llvm::Value* counterValue = ir_builder.CreateLoad(unsignedLongType, counterVariable, "counter");
        llvm::Value* conditionCheck = ir_builder.CreateICmpULT(counterValue, numIterations, "loop.cond");
        llvm::BasicBlock* AfterBB = llvm::BasicBlock::Create(context, "afterloop", TheFunction);
        ir_builder.CreateCondBr(conditionCheck, LoopBB, AfterBB);
        ir_builder.SetInsertPoint(AfterBB);
        llvm::Value* incrementValue = llvm::ConstantInt::get(unsignedLongType, 1);
        llvm::Value* nextCounterValue = ir_builder.CreateAdd(counterValue, incrementValue, "nextcounter");
        ir_builder.CreateStore(nextCounterValue, counterVariable);

        if (!bodyExpr->codeGen())
            return nullptr;
        return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(context));
    } // REPEAT_UNTIL
}
