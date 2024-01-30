//
// Created by robcholz on 12/19/23.
//
#include "type/Type.hpp"
#include "Info.hpp"
#include "ReservedWords.hpp"


Type::Type(const std::string& type) {
    // TODO we assume that type is a elementary type
    this->type = ssa::from_string<ssa::Elementary>(type);
    this->bitwidth = ssa::getBitwidth(this->type);
}

Type::Type(ssa::Elementary type) {
    this->type = type;
    this->bitwidth = ssa::getBitwidth(type);
}

ssa::Elementary Type::getWrappedType() const {
    return type;
}

uint64_t Type::getBitWidth() const {
    return bitwidth;
}

bool Type::isFloat() const {
    if (type == ssa::Elementary::F16) return true;
    if (type == ssa::Elementary::F32) return true;
    if (type == ssa::Elementary::F64) return true;
    return false;
}

bool Type::isInteger() const {
    if (type == ssa::Elementary::I8) return true;
    if (type == ssa::Elementary::I16) return true;
    if (type == ssa::Elementary::I32) return true;
    if (type == ssa::Elementary::I64) return true;
    if (type == ssa::Elementary::I128) return true;
    if (type == ssa::Elementary::ISIZE) return true;
    if (type == ssa::Elementary::U8) return true;
    if (type == ssa::Elementary::U16) return true;
    if (type == ssa::Elementary::U32) return true;
    if (type == ssa::Elementary::U64) return true;
    if (type == ssa::Elementary::U128) return true;
    if (type == ssa::Elementary::USIZE) return true;
    return false;
}

bool Type::isSigned() const {
    if (isFloat())
        return true;
    if (isInteger()) {
        if (type == ssa::Elementary::I8) return true;
        if (type == ssa::Elementary::I16) return true;
        if (type == ssa::Elementary::I32) return true;
        if (type == ssa::Elementary::I64) return true;
        if (type == ssa::Elementary::I128) return true;
        if (type == ssa::Elementary::ISIZE) return true;
        return false;
    }
    return false;
}

bool Type::isVoid() const {
    return type == ssa::Elementary::VOID;
}

const Type& Type::getType() const {
    return *this;
}

llvm::Type* Type::toLLVMType() const {
    auto& context = Info::getInstance().getLLVMContext();
    if (isInteger()) {
        return llvm::IntegerType::get(context, getBitWidth());
    } else if (isFloat()) {
        const auto bit_width = getBitWidth();
        if (bit_width == 16) {
            return llvm::Type::getHalfTy(context);
        }
        if (bit_width == 32) {
            return llvm::Type::getFloatTy(context);
        }
        if (bit_width == 64) {
            return llvm::Type::getDoubleTy(context);
        }
        // TODO f128?
    }
    if (isVoid()) {
        return llvm::Type::getVoidTy(context);
    }
    spdlog::error("unhandled exception type");
    // TODO handle exception type
    std::terminate();
}

void Type::tryStandardizeTypeValue(llvm::Value** left, llvm::Value** right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& context = Info::getInstance().getLLVMContext();
    const auto left_type = (*left)->getType();
    const auto right_type = (*right)->getType();

    if (left_type->isIntegerTy() && right_type->isFloatingPointTy()) {
        *left = ir_builder.CreateSIToFP(*left, llvm::Type::getDoubleTy(context));
    }
    if (right_type->isIntegerTy() && left_type->isFloatingPointTy()) {
        *right = ir_builder.CreateSIToFP(*right, llvm::Type::getDoubleTy(context));
    }
}

void Type::tryStandardizeValueType(llvm::Value** left, const llvm::Type* targetType) {
    auto& ir_builder = Info::getInstance().getIRBuilder();
    auto& context = Info::getInstance().getLLVMContext();
    const auto left_type = (*left)->getType();

    if (left_type->isIntegerTy() && targetType->isFloatingPointTy()) {
        *left= ir_builder.CreateSExt(*left,llvm::Type::getDoubleTy(context));
        return;
    }
    if (targetType->isIntegerTy() && left_type->isFloatingPointTy()) {
        // TODO sematics error
        spdlog::error("Sematics Error");
        return;
    }
    if ((left_type->isIntegerTy() && targetType->isIntegerTy()) ||
        (left_type->isFloatingPointTy() && targetType->isFloatingPointTy())) {
        return;
    }
    spdlog::error("Unhandled Error in tryReturnStandardizedValueType: from " + to_string(left_type)
                  + " to " + to_string(targetType));
}

void Type::trySyncTypeValue(llvm::Value** left, llvm::Value** right) {
    auto& ir_builder = Info::getInstance().getIRBuilder();

    tryStandardizeTypeValue(left, right);

    const auto left_type = (*left)->getType();
    const auto right_type = (*right)->getType();

    if (left_type->isIntegerTy()) {
        const auto& l_width = left_type->getIntegerBitWidth();
        const auto& r_width = right_type->getIntegerBitWidth();
        if (l_width > r_width)
            *right = ir_builder.CreateZExt(*right, left_type);
        else if (l_width < r_width)
            *left = ir_builder.CreateZExt(*left, right_type);
    }
    if (left_type->isFloatingPointTy()) {
        const auto& l_width = left_type->getPrimitiveSizeInBits();
        const auto& r_width = right_type->getPrimitiveSizeInBits();
        if (l_width > r_width)
            *right = ir_builder.CreateFPExt(*right, left_type);
        else if (l_width < r_width)
            *left = ir_builder.CreateFPExt(*left, right_type);
    }
}

llvm::Type* Type::returnSyncType(llvm::Value* left, llvm::Value* right) {
    // TODO toy function
    const auto& l_type=left->getType()->getIntegerBitWidth();
    const auto& r_type=right->getType()->getIntegerBitWidth();
    if(l_type>r_type)
        return left->getType();
    else
        return right->getType();
}

llvm::Value* Type::tryReturnSyncTypeValue(llvm::Value* left, llvm::Type* targetType) {
    auto& ir_builder = Info::getInstance().getIRBuilder();

    tryStandardizeValueType(&left, targetType);

    const auto left_type = left->getType();

    if (left_type->isIntegerTy()) {
        const unsigned l_width = left_type->getPrimitiveSizeInBits();
        const unsigned r_width = targetType->getPrimitiveSizeInBits();
        if (l_width > r_width) {
            spdlog::error("Sematics Error, from bigger bits to smaller bits");
            return nullptr;
        }
        if (l_width < r_width)
            return ir_builder.CreateZExt(left, targetType);
        return left;
    }
    if (left_type->isFloatingPointTy()) {
        const unsigned l_width = left_type->getPrimitiveSizeInBits();
        const unsigned r_width = targetType->getPrimitiveSizeInBits();
        if (l_width > r_width) {
            spdlog::error("Sematics Error, from bigger bits to smaller bits");
            return nullptr;
        }
        if (l_width < r_width)
            return ir_builder.CreateFPExt(left, targetType);
        return left;
    }

    spdlog::error("Unhandled Error in tryReturnSyncTypeValue: from " + to_string(left_type)
                  + " to " + to_string(targetType));
    return nullptr;
}

std::string Type::to_string(const llvm::Type* type) {
    std::string typeName;
    llvm::raw_string_ostream rso(typeName);
    type->print(rso);
    return rso.str();
}
