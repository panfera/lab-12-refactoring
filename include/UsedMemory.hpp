//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_USEDMEMORY_HPP_
#define INCLUDE_USEDMEMORY_HPP_

#include "PageContainer.hpp"
#include <string>
#include <vector>

class UsedMemory : public IDataLoadedObserver, public IRawLoadedObserver {
 public:
  explicit UsedMemory(PageContainer& page);

  void OnDataLoad(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items) override;

  void OnRawDataLoad(const std::vector<std::string>& old_items,
                     const std::vector<std::string>& new_items) override;

  size_t used() const;

 private:
  const Log* log_;
  PageContainer* page_;
  size_t used_ = 0;
};

#endif  // INCLUDE_USEDMEMORY_HPP_
