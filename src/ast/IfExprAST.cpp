//
// Created by robcholz on 11/28/23.
//
#include "ast/IfExprAST.hpp"
#include "Info.hpp"
#include "type/Type.hpp"


IfExprAST::IfExprAST(std::unique_ptr<ExprAST> condition, std::unique_ptr<ExprAST> thenExpr,
                     std::unique_ptr<ExprAST> elseExpr) {
    this->condition = std::move(condition);
    this->thenExpr = std::move(thenExpr);
    this->elseExpr = std::move(elseExpr);
}

llvm::Value* IfExprAST::codeGen() {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& context = Info::getInstance().getLLVMContext();

    auto *cond_value = this->condition->codeGen();
    if (!cond_value)
        return nullptr;
    const auto func = ir_builder.GetInsertBlock()->getParent();
    auto then_func_block = llvm::BasicBlock::Create(context, "btrue", func);
    auto else_func_block = llvm::BasicBlock::Create(context, "bfalse");
    const auto merge_func_block = llvm::BasicBlock::Create(context, "end");
    ir_builder.CreateCondBr(cond_value, then_func_block, else_func_block);
    ir_builder.SetInsertPoint(then_func_block);
    const auto then_value = this->thenExpr->codeGen();
    if (!then_value)
        return nullptr;
    ir_builder.CreateBr(merge_func_block);
    then_func_block = ir_builder.GetInsertBlock();
    func->insert(func->end(), else_func_block);
    ir_builder.SetInsertPoint(else_func_block);
    const auto else_value = this->elseExpr->codeGen();
    if (!else_value)
        return nullptr;
    ir_builder.CreateBr(merge_func_block);
    else_func_block = ir_builder.GetInsertBlock();
    func->insert(func->end(), merge_func_block);
    ir_builder.SetInsertPoint(merge_func_block);
    // TODO result type fix
    const auto result = ir_builder.CreatePHI(
        Type::returnSyncType(then_value,else_value),
        2,
        "iftmp"
        );
    result->addIncoming(then_value, then_func_block);
    result->addIncoming(else_value, else_func_block);
    return result;
}
