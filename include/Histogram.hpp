//
// Created by hacker on 6/6/21.
//

#ifndef TEMPLATE_HISTOGRAM_HPP
#define TEMPLATE_HISTOGRAM_HPP
#include "PageContainer.hpp"

class Histogram : IDataLoadedObserver, ISkippedObserver {
 public:
  Histogram(PageContainer& page);
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

#endif  // TEMPLATE_HISTOGRAM_HPP
