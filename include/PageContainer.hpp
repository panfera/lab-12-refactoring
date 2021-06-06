//
// Created by hacker on 6/6/21.
//

#ifndef TEMPLATE_PAGECONTAINER_HPP
#define TEMPLATE_PAGECONTAINER_HPP

#include "Log.hpp"
#include "Observer.hpp"
#include "iostream"
#include <fstream>      // ifstream

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

#endif  // TEMPLATE_PAGECONTAINER_HPP
