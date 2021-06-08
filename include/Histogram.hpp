//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_HISTOGRAM_HPP_
#define INCLUDE_HISTOGRAM_HPP_
#include "PageContainer.hpp"
#include <vector>

class Histogram : IDataLoadedObserver, ISkippedObserver {
 public:
  explicit Histogram(PageContainer& page);
  void OnDataLoad(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items) override;

  void OnLoaded(const std::vector<Item>& new_items) override{};

  void Skip(const Item& item) override;

  float GetAvg() const;

  int32_t GetCount() const;

 private:
  bool finish_;
  float avg_;
  int32_t count_skip_;
  PageContainer* page_;
};

#endif  // INCLUDE_HISTOGRAM_HPP_
