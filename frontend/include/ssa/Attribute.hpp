//
// Created by robcholz on 2/18/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_ATTRIBUTE_HPP
#define SSAKURA_FRONTEND_ATTRIBUTE_HPP

#ifdef __GNUC__
#define SSA_FORCE_INLINE __attribute__((always_inline))
#elif defined(__clang__)
#define SSA_FORCE_INLINE __attribute__((always_inline))
#else
#define SSA_FORCE_INLINE inline
#endif

#endif  // SSAKURA_FRONTEND_ATTRIBUTE_HPP
