//
// Created by hacker on 6/6/21.
//
// Copyright 2021 pan_fera

#ifndef INCLUDE_OBSERVER_HPP_
#define INCLUDE_OBSERVER_HPP_

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Data.hpp"

class IDataLoadedObserver {
 public:
  virtual ~IDataLoadedObserver() = default;
  virtual void OnDataLoad(const std::vector<Item>& old_items,
                          const std::vector<Item>& new_items) = 0;
};

class IRawLoadedObserver {
 public:
  virtual ~IRawLoadedObserver() = default;
  virtual void OnRawDataLoad(const std::vector<std::string>& old_items,
                             const std::vector<std::string>& new_items) = 0;
};

class ISkippedObserver {
 public:
  virtual ~ISkippedObserver() = default;
  virtual void Skip(const Item& item) = 0;
};

class ILoadedObserver{
 public:
  virtual ~ILoadedObserver() = default;
  virtual void OnLoaded(const std::vector<Item>& new_items) = 0;
};

class ISubject {
 public:
  virtual ~ISubject() {}
  virtual void AttachDataLoaded(IDataLoadedObserver* observer) = 0;
  virtual void AttachRowLoaded(IRawLoadedObserver* observer) = 0;
  virtual void AttachSkipped(ISkippedObserver* observer) = 0;
  virtual void AttachLoaded(ILoadedObserver* observer) = 0;

  [[maybe_unused]] virtual void DetachDataLoaded(
      IDataLoadedObserver* observer) = 0;
  [[maybe_unused]] virtual void DetachRowLoaded(
      IRawLoadedObserver* observer) = 0;
  [[maybe_unused]] virtual void DetachSkipped(
      ISkippedObserver* observer) = 0;
  [[maybe_unused]] virtual void DetachLoaded(
      ILoadedObserver* observer) = 0;

  virtual void NotifyDataLoadedObservers(
      const std::vector<Item>& old_items,
      const std::vector<Item>& new_items) = 0;
  virtual void NotifyRowLoadedObservers(
      const std::vector<std::string>& old_items,
      const std::vector<std::string>& new_items) = 0;
  virtual void NotifySkippedObservers(
      const Item& item) = 0;
  virtual void NotifyLoadedObservers(
      const std::vector<Item>& new_items) = 0;
};

#endif  // INCLUDE_OBSERVER_HPP_
