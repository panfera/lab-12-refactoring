//
// Created by hacker on 6/6/21.
//

#ifndef TEMPLATE_USEDMEMORY_HPP
#define TEMPLATE_USEDMEMORY_HPP

#include "PageContainer.hpp"

class UsedMemory : IDataLoadedObserver, IRawLoadedObserver {
 public:
  UsedMemory(PageContainer& page);

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

#endif  // TEMPLATE_USEDMEMORY_HPP
