#ifndef TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERFACTORYSTORAGEIMPL1_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERFACTORYSTORAGEIMPL1_H_

#include <map>

#include "plugin/storages/pluginproviderfactorystorage.h"


class PluginProviderFactoryStorageImpl1: public PluginProviderFactoryStorage {
 public:
  void addPluginProviderFactoryView(const std::string &name, const std::shared_ptr<QWidget> &view) override;
  std::shared_ptr<QWidget> getPluginProviderFactoryView(const std::string &name) override;
  bool removePluginProviderFactoryView(const std::string &name) override;

  std::vector<std::string> getPluginProviderFactoryNames() override;

  int getRowCount() override;

 private:
  std::map<std::string, std::shared_ptr<QWidget>> _factory_views;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERFACTORYSTORAGEIMPL1_H_
