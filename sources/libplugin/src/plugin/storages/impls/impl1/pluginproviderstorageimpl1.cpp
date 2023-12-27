#include "plugin/storages/impls/impl1/pluginproviderstorageimpl1.h"


std::shared_ptr<PluginProvider> PluginProviderStorageImpl1::addDevice(const std::string &uid,
                                                                      const std::shared_ptr<PluginProvider> &device) {
  std::shared_ptr<PluginProvider> result = nullptr;
  if (_plugin_providers.count(uid) == 0) {
    _plugin_providers.insert({uid, device});
    result = device;
  }
  return result;
}

std::shared_ptr<PluginProvider> PluginProviderStorageImpl1::getDevice(const std::string &uid) {
  std::shared_ptr<PluginProvider> result = nullptr;
  if (_plugin_providers.count(uid) != 0) {
    result = _plugin_providers.at(uid);
  }
  return result;
}

bool PluginProviderStorageImpl1::removeDevice(const std::string &uid) {
  return false;
}

std::vector<std::string> PluginProviderStorageImpl1::getDeviceUIDByName(const std::string &name) {
  return std::vector<std::string>();
}
