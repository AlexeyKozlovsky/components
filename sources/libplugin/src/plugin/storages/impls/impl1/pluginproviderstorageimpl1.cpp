
#include "plugin/storages/impls/impl1/pluginproviderstorageimpl1.h"

std::shared_ptr<PluginProvider> PluginProviderStorageImpl1::addDevice(const std::string &uid,
                                                                      const std::shared_ptr<PluginProvider> &device) {
  std::shared_ptr<PluginProvider> result = nullptr;
  if (_plugin_providers.count(uid) == 0) {
    _plugin_providers.insert({uid, device});
    result = device;
    rowInsertedNotify();
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
  if (_plugin_providers.count(uid) != 0) {
    _plugin_providers.erase(uid);
    rowRemovedNotify();
    return true;
  }
  return false;
}

std::vector<std::string> PluginProviderStorageImpl1::getDeviceUIDByName(const std::string &name) {
  return std::vector<std::string>();
}

std::vector<std::pair<std::string, std::shared_ptr<PluginProvider>>> PluginProviderStorageImpl1::getAllDevices() {
  std::vector<std::pair<std::string, std::shared_ptr<PluginProvider>>> result(std::begin(_plugin_providers), std::end(_plugin_providers));
  return result;
}

int PluginProviderStorageImpl1::getDevicesCount() {
  return _plugin_providers.size();
}


int PluginProviderStorageImpl1::getRowCount() {
  return getDevicesCount();
}



