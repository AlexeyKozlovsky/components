#ifndef TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_PLUGINPROVIDERSTORAGE_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_PLUGINPROVIDERSTORAGE_H_

#include <memory>


#include "modbuswrappers/modbuswrapperstorage.h"
#include "threadpooling/threadpoolbuilder.h"
#include "plugin/deviceplugins/pluginprovider.h"

#include <utils/storages/basestorage.h>


// TODO: Добавить device model storage


class PluginProviderStorage: public BaseStorage {
 public:

  // TODO: Продумать хранилище и дописать его
  virtual std::shared_ptr<PluginProvider> addDevice(const std::string &uid, const std::shared_ptr<PluginProvider> &device) = 0;
  virtual std::shared_ptr<PluginProvider> getDevice(const std::string &uid) = 0;
  virtual bool removeDevice(const std::string &uid) = 0;

  virtual std::vector<std::string> getDeviceUIDByName(const std::string &name) = 0;

  virtual std::vector<std::pair<std::string, std::shared_ptr<PluginProvider>>> getAllDevices() = 0;
  virtual int getDevicesCount() = 0;

};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_PLUGINPROVIDERSTORAGE_H_
