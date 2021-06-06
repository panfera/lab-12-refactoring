//
// Created by hacker on 6/6/21.
//

#include "PageContainer.hpp"

void PageContainer::Load(std::istream& io, float threshold) {
  std::vector<std::string> raw_data;

  while (!io.eof()) {
    std::string line;
    std::getline(io, line, '\n');
    raw_data.push_back(std::move(line));
  }

  if (raw_data.size() < kMinLines) {
    log_->Write("too small input stream");
    throw std::runtime_error("too small input stream");
  }

  // memory_counter_->OnRawDataLoad(raw_data_, raw_data);
  NotifyRowLoadedObservers(raw_data_, raw_data);
  raw_data_ = std::move(raw_data);

  std::vector<Item> data;
  std::set<std::string> ids;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      log_->Write("already seen");
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      // stat_sender_.Skip(item);
      NotifySkippedObservers(item);
    }
  }

  if (data.size() < kMinLines) {
    log_->Write("oops");
    throw std::runtime_error("oops");
  }

  // memory_counter_->OnDataLoad(data_, data);
  NotifyDataLoadedObservers(data_, data);
  // stat_sender_.OnLoaded(data);
  NotifyLoadedObservers(data);
  data_ = std::move(data);
}

const Item& PageContainer::ByIndex(size_t i) const { return data_[i]; }

const Item& PageContainer::ById(const std::string& id) const {
  auto it = std::find_if(std::begin(data_), std::end(data_),
                         [&id](const auto& i) { return id == i.id; });
  return *it;
}

void PageContainer::Reload(float threshold) {
  std::vector<Item> data;
  std::set<std::string> ids;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);
    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      // stat_sender_.Skip(item);
      NotifySkippedObservers(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  // memory_counter_->OnDataLoad(data_, data);
  NotifyDataLoadedObservers(data_, data);

  // stat_sender_.OnLoaded(data);
  NotifyLoadedObservers(data);
  data_ = std::move(data);
}

PageContainer::PageContainer() : log_(&Log::getInstance()) {}

void PageContainer::AttachDataLoaded(IDataLoadedObserver* observer) {
  list_dlobservers_.push_back(observer);
}

void PageContainer::AttachRowLoaded(IRawLoadedObserver* observer) {
  list_rlobservers_.push_back(observer);
}

void PageContainer::AttachSkipped(ISkippedObserver* observer) {
  list_sobservers_.push_back(observer);
}

void PageContainer::DetachDataLoaded(IDataLoadedObserver* observer) {
  list_dlobservers_.remove(observer);
}

void PageContainer::DetachRowLoaded(IRawLoadedObserver* observer) {
  list_rlobservers_.remove(observer);
}

void PageContainer::DetachSkipped(ISkippedObserver* observer) {
  list_sobservers_.remove(observer);
}

void PageContainer::NotifyDataLoadedObservers(
    const std::vector<Item>& old_items, const std::vector<Item>& new_items) {
  for (auto& it : list_dlobservers_) it->OnDataLoad(old_items, new_items);
}

void PageContainer::NotifyRowLoadedObservers(
    const std::vector<std::string>& old_items,
    const std::vector<std::string>& new_items) {
  for (auto& it : list_rlobservers_) it->OnRawDataLoad(old_items, new_items);
}

void PageContainer::NotifySkippedObservers(const Item& item) {
  for (auto& it : list_sobservers_) it->Skip(item);
}

void PageContainer::NotifyLoadedObservers(const std::vector<Item>& new_items) {
  for (auto& it : list_sobservers_) it->OnLoaded(new_items);
}
