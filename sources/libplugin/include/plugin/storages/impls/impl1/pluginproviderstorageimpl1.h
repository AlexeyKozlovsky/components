#ifndef TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERSTORAGEIMPL1_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERSTORAGEIMPL1_H_

#include "plugin/storages/pluginproviderstorage.h"
#include <plugin/export.h>


class PLUGIN_EXPORT PluginProviderStorageImpl1: public PluginProviderStorage {
 public:
  std::shared_ptr<PluginProvider> addDevice(const std::string &uid,
                                            const std::shared_ptr<PluginProvider> &device) override;
  std::shared_ptr<PluginProvider> getDevice(const std::string &uid) override;
  bool removeDevice(const std::string &uid) override;
  std::vector<std::string> getDeviceUIDByName(const std::string &name) override;

  std::vector<std::pair<std::string, std::shared_ptr<PluginProvider>>> getAllDevices() override;
  int getDevicesCount() override;
  int getRowCount() override;

 private:
  std::map<std::string, std::shared_ptr<PluginProvider>> _plugin_providers;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_IMPLS_IMPL1_PLUGINPROVIDERSTORAGEIMPL1_H_
