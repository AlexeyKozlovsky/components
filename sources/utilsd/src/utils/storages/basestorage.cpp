#include <algorithm>
#include "utils/storages/basestorage.h"

void BaseStorage::addDimChangeNotifier(const std::shared_ptr<DimChangeNotifier> &notifier) {
  if (notifier != nullptr) {
    _dim_change_notifiers.push_back(notifier);
  }
}

void BaseStorage::removeDimChangeNotifier(const std::shared_ptr<DimChangeNotifier> &notifier) {

}

void BaseStorage::rowInsertedNotify() {
  updateNotifiers();

  int rows_count = getRowCount();
  int row_to_add = 1;
  std::for_each(std::begin(_dim_change_notifiers), std::end(_dim_change_notifiers), [&](const std::shared_ptr<DimChangeNotifier> &notifier) {
    if (notifier != nullptr) {
      notifier->insertRows(rows_count, row_to_add);
    }
  });

}
void BaseStorage::rowRemovedNotify() {
  updateNotifiers();

  int rows_count = getRowCount();
  int row_to_remove = 1;
  std::for_each(std::begin(_dim_change_notifiers), std::end(_dim_change_notifiers), [&](const std::shared_ptr<DimChangeNotifier> &notifier) {
    if (notifier != nullptr) {
      notifier->removeRows(rows_count, row_to_remove);
    }
  });
}

void BaseStorage::updateNotifiers() {
  auto it = std::remove_if(std::begin(_dim_change_notifiers), std::end(_dim_change_notifiers), [&](const std::shared_ptr<DimChangeNotifier> &notifier) {
    return notifier == nullptr;
  });

  _dim_change_notifiers.erase(it, std::end(_dim_change_notifiers));
}
