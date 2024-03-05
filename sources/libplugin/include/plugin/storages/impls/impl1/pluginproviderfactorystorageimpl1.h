#ifndef TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERFACTORYSTORAGEIMPL1_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERFACTORYSTORAGEIMPL1_H_

#include <map>

#include "plugin/storages/pluginproviderfactorystorage.h"
#include <plugin/export.h>


class PLUGIN_EXPORT PluginProviderFactoryStorageImpl1: public PluginProviderFactoryStorage {
 public:
  void addPluginProviderFactoryView(const std::string &name, const std::shared_ptr<PluginProviderFactory> &plugin_provider_factory) override;
  std::shared_ptr<QWidget> getPluginProviderFactoryView(const std::string &name) override;
  bool removePluginProviderFactoryView(const std::string &name) override;

  std::vector<std::string> getPluginProviderFactoryNames() override;

  int getRowCount() override;
  std::shared_ptr<PluginProviderFactory> getPluginProviderFactory(const std::string &name) override;

 private:
  std::map<std::string, std::shared_ptr<PluginProviderFactory>> _factory_providers;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERFACTORYSTORAGEIMPL1_H_
