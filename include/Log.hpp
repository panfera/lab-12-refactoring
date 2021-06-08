//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_

#include <iostream>

class Log {
 public:
  static Log& getInstance();
  [[maybe_unused]] void set(size_t level);
  void Write(std::string_view message) const;
  void WriteDebug(std::string_view message) const;

 private:
  Log();
  Log(const Log&) = delete;
  Log& operator=(Log&) = delete;
  size_t level_;
  mutable std::ostream* out_;
};

#endif  // INCLUDE_LOG_HPP_
