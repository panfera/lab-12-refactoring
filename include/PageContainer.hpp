//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_PAGECONTAINER_HPP_
#define INCLUDE_PAGECONTAINER_HPP_

#include "Log.hpp"
#include "Observer.hpp"
#include "iostream"
#include <fstream>      // ifstream
#include <string>
#include <vector>
#include <list>

class PageContainer : ISubject {
 public:
  void Load(std::istream& io, float threshold);

  const Item& ByIndex(size_t i) const;

  const Item& ById(const std::string& id) const;

  void Reload(float threshold);

  PageContainer();

  void AttachDataLoaded(IDataLoadedObserver* observer) override;

  void AttachRowLoaded(IRawLoadedObserver* observer) override;

  void AttachSkipped(ISkippedObserver* observer) override;

  void DetachDataLoaded(IDataLoadedObserver* observer) override;

  void DetachRowLoaded(IRawLoadedObserver* observer) override;

  void DetachSkipped(ISkippedObserver* observer) override;

 private:
  void NotifyDataLoadedObservers(const std::vector<Item>& old_items,
                                 const std::vector<Item>& new_items) override;

  void NotifyRowLoadedObservers(
      const std::vector<std::string>& old_items,
      const std::vector<std::string>& new_items) override;

  void NotifySkippedObservers(const Item& item) override;

  void NotifyLoadedObservers(const std::vector<Item>& new_items) override;

  const Log* log_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
  std::list<IDataLoadedObserver*> list_dlobservers_;
  std::list<IRawLoadedObserver*> list_rlobservers_;
  std::list<ISkippedObserver*> list_sobservers_;
};

#endif  // INCLUDE_PAGECONTAINER_HPP_
