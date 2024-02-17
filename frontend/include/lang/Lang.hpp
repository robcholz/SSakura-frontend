//
// Created by robcholz on 2/1/24.
//
#pragma once

#ifndef SSAKURA_FRONTEND_LANG_HPP
#define SSAKURA_FRONTEND_LANG_HPP

namespace ssa {
class Lang {
 public:
  Lang() = delete;
  ~Lang() = delete;
  Lang& operator=(Lang&) = delete;

  static void init();
};
}  // namespace ssa

#endif  // SSAKURA_FRONTEND_INCLUDE_LANG_LANG_HPP
