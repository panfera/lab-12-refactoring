//
// Created by hacker on 6/6/21.
//

#ifndef TEMPLATE_STATSENDER_HPP
#define TEMPLATE_STATSENDER_HPP
#include "PageContainer.hpp"

class StatSender : ISkippedObserver {
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

#endif  // TEMPLATE_STATSENDER_HPP
