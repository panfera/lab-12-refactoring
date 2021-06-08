//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_DATA_HPP_
#define INCLUDE_DATA_HPP_
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

static constexpr size_t kMinLines = 10;

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};

#endif  // INCLUDE_DATA_HPP_
