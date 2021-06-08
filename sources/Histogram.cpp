//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#include "Histogram.hpp"

Histogram::Histogram(PageContainer& page) : finish_(false), avg_(0),
                                            count_skip_(0), page_(&page){
  page_->AttachSkipped(this);
  page_->AttachDataLoaded(this);
}
void Histogram::OnDataLoad(const std::vector<Item>& old_items,
                           const std::vector<Item>& new_items) {
  float sum = 0;
  for (auto& it : new_items)
    sum += it.score;
  avg_ = sum / new_items.size();
  finish_ = true;
}
void Histogram::Skip(const Item& item) {
  if (finish_){
    finish_ = false;
    count_skip_ = 0;
  }
  ++count_skip_;
}

float Histogram::GetAvg() const { return avg_; }

int32_t Histogram::GetCount() const { return count_skip_; }
