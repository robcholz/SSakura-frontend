//
// Created by robcholz on 3/10/24.
//
#pragma once

#ifndef ANEMOS_LIBRARYLOADER_HPP
#define ANEMOS_LIBRARYLOADER_HPP

#include <expected>
#include <string>
#include <string_view>

#ifdef __linux__
#define LINUX_MACOS
#endif
#ifdef __APPLE__
#define LINUX_MACOS
#endif
#ifdef _WIN32
#define WINDOWS
#endif

#ifdef LINUX_MACOS
#include <dlfcn.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

namespace anemos {
class LibraryLoader {
 public:
  explicit LibraryLoader(std::string library) {
    this->library = std::move(library);
    this->libraryHandler = nullptr;
  }
  ~LibraryLoader() = default;

  LibraryLoader(LibraryLoader&) = delete;
  LibraryLoader(LibraryLoader&&) = delete;

  void load() {
#ifdef LINUX_MACOS
    libraryHandler = dlopen(library.c_str(), RTLD_LAZY);
#endif
#ifdef WINDOWS
    libraryHandler = LoadLibrary(library.c_str());
#endif
  }
  void close() {
#ifdef LINUX_MACOS
    dlclose(libraryHandler);
#endif
#ifdef WINDOWS
    FreeLibrary(libraryHandler);
#endif
  }

  std::expected<void*, std::string> invoke(std::string_view function) {
#ifdef LINUX_MACOS
    void* function_handler = dlsym(libraryHandler, function.data());
    if (function_handler == nullptr) {
      std::string error = dlerror();
      return std::unexpected(std::move(error));
    }
    return {function_handler};
#endif
#ifdef WINDOWS
    void* functionHandler = GetProcAddress(libraryHandler, function.data());
    if (functionHandler == nullptr) {
      std::string error = "error occured: " + std::to_string(GetLastError());
      return std::unexpected(error);
    }
    return {functionHandler};
#endif
  }

 private:
  std::string library;

#ifdef LINUX_MACOS
  void* libraryHandler;
#endif
#ifdef WINDOWS
  HINSTANCE libraryHandler;
#endif
};
}  // namespace anemos

#ifdef WINDOWS
#undef WINDOWS
#endif
#ifdef LINUX_MACOS
#undef LINUX_MACOS
#endif

#endif  // ANEMOS_LIBRARYLOADER_HPP
