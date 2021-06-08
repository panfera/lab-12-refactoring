//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_STATSENDER_HPP_
#define INCLUDE_STATSENDER_HPP_
#include "PageContainer.hpp"
#include <vector>

class StatSender : public ISkippedObserver, public ILoadedObserver {
 public:
  StatSender(PageContainer& page);

  void OnLoaded(const std::vector<Item>& new_items) override;

  void Skip(const Item& item) override;

 protected:
  virtual void AsyncSend(const std::vector<Item>& items, std::string_view path);

  const Log* log_;
  PageContainer* page_;
  std::ofstream fstr{"network", std::ios::binary};
};

#endif  // INCLUDE_STATSENDER_HPP_

