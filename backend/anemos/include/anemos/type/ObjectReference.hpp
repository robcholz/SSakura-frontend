//
// Created by robcholz on 2/20/24.
//
#pragma once

#ifndef ANEMOS_OBJECTREFERENCE_HPP
#define ANEMOS_OBJECTREFERENCE_HPP

#include <string>

namespace anemos {
class ObjectReference {
 public:
  ObjectReference()= default;
  explicit ObjectReference(std::string name);

 private:
  std::string objectName;
};
}  // namespace anemos

#endif  // ANEMOS_OBJECTREFERENCE_HPP
