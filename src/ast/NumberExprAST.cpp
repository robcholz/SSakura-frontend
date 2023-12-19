//
// Created by robcholz on 11/25/23.
//
#include <complex>
#include <llvm/IR/Constants.h>
#include "ast/NumberExprAST.hpp"
#include "Info.hpp"


NumberExprAST::NumberExprAST(const std::string& number) {
    auto iterator = number.rbegin();
    const auto iterator_end = number.rend();

    integer_t integer_pt = 0;
    floating_t floating_pt = 0.f;
    size_t floating_pt_length = 0;
    bool is_integer = true;

    integer_t pow_pt = 0;
    bool is_scientific = false;

    size_t at = 1;
    char num_at = ' ';

    for (; iterator != iterator_end; ++iterator) {
        num_at = *iterator;
        if (isnumber(num_at)) {
            integer_pt = (num_at - '0') * static_cast<long>(at) + integer_pt;
            ++at;
        } else {
            if (num_at == '.' && is_integer) {
                // move the integer part to decimal part
                floating_pt = static_cast<floating_t>(integer_pt) / std::pow(10, at);
                is_integer = false;
                integer_pt = 0;
                floating_pt_length = at;
                at = 1;
            } // handle pure floating number
            else if (num_at == 'e' && !is_scientific) {
                pow_pt = integer_pt;
                is_scientific = true;
                integer_pt = 0;
                at = 1;
            }
        }
    }
    if (!is_integer)
        floating_pt += integer_pt;

    if (is_scientific) {
        if (is_integer) {
            integer_pt = static_cast<integer_t>(std::pow(integer_pt, pow_pt));
        } // base is integer
        else {
            if (floating_pt_length == pow_pt) {
                integer_pt = static_cast<integer_t>(std::pow(floating_pt, pow_pt));
                is_integer = true;
            } // if the decial pos equals pow part, it is still integer
            else {
                floating_pt = std::pow(floating_pt, pow_pt);
            } // floating for sure
        }
    }

    if (is_integer) {
        this->integer = integer_pt;
        this->floating = 0.f;
        this->type = INTEGER;
    } else {
        this->integer = 0;
        this->floating = floating_pt;
        this->type = FLOATING;
    }
}

llvm::Value* NumberExprAST::codeGen() {
    //if(this->type==INTEGER)
    //    return llvm::ConstantInt::get(Info::getInstance().getLLVMContext(),llvm::APInt((int)this->integer)); // TODO
    return llvm::ConstantFP::get(Info::getInstance().getLLVMContext(),llvm::APFloat((double)this->integer)); // TODO
}

