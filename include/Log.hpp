//
// Created by hacker on 6/6/21.
//

#ifndef TEMPLATE_LOG_HPP
#define TEMPLATE_LOG_HPP

#include <iostream>

class Log {
 public:
  static Log& getInstance();
  void set(size_t level);
  void Write(std::string_view message) const;
  void WriteDebug(std::string_view message) const;

 private:
  Log();
  Log(const Log&) = delete;
  Log& operator=(Log&) = delete;
  size_t level_;
  mutable std::ostream* out_;
};

#endif  // TEMPLATE_LOG_HPP
